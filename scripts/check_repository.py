#!/usr/bin/env python3
"""Validate the public repository boundary without external dependencies."""

from __future__ import annotations

import json
import re
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
MAX_FILE_BYTES = 10 * 1024 * 1024

REQUIRED_PATHS = (
    ".gitattributes",
    ".gitignore",
    ".github/workflows/ci.yml",
    "FashionRotunda.uproject",
    "README.md",
    "Source/FashionRotunda/FashionRotunda.Build.cs",
)

EXCLUDED_ROOTS = {
    ".idea",
    ".vs",
    "Binaries",
    "Build",
    "Content",
    "DerivedDataCache",
    "Intermediate",
    "Releases",
    "Saved",
    "StagedBuilds",
}

EXCLUDED_SUFFIXES = {
    ".dll",
    ".dmp",
    ".exe",
    ".lib",
    ".obj",
    ".pak",
    ".pdb",
    ".pch",
    ".sarif",
    ".tmp",
    ".ucas",
    ".utoc",
    ".user",
}

LOCAL_ONLY_NAMES = {
    "A" + "GENTS.md",
    "CL" + "AUDE.md",
}

LOCAL_ONLY_PARTS = (
    "." + "co" + "dex",
    "." + "cl" + "aude",
)

LOCAL_ONLY_PHRASES = (
    "a" + "gents.md",
    "co" + "dex",
    "cl" + "aude",
    "chat" + "gpt",
    "artificial " + "intelligence",
)

SECRET_PATTERNS = (
    re.compile(r"-----BEGIN (?:RSA |EC |OPENSSH |DSA )?PRIVATE KEY-----"),
    re.compile(r"\bgh[pousr]_[A-Za-z0-9]{20,}\b"),
    re.compile(r"\bgithub_pat_[A-Za-z0-9_]{20,}\b"),
    re.compile(r"\b(?:AKIA|ASIA)[0-9A-Z]{16}\b"),
    re.compile(r"\bAIza[0-9A-Za-z_-]{30,}\b"),
    re.compile(r"\bsk-(?:live|test)-[A-Za-z0-9]{16,}\b"),
    re.compile(r"(?i)\b(?:password|client_secret|api[_-]?key|securitytoken)[ \t]*[=:][ \t]*[\"']?[A-Za-z0-9_./+=-]{8,}"),
)


def tracked_paths() -> list[Path]:
    result = subprocess.run(
        ["git", "ls-files", "-z"],
        cwd=ROOT,
        check=True,
        capture_output=True,
    )
    return [Path(value.decode("utf-8")) for value in result.stdout.split(b"\0") if value]


def is_probably_binary(data: bytes) -> bool:
    return b"\0" in data[:8192]


def validate_descriptor(errors: list[str]) -> None:
    descriptor_path = ROOT / "FashionRotunda.uproject"
    try:
        descriptor = json.loads(descriptor_path.read_text(encoding="utf-8-sig"))
    except (OSError, json.JSONDecodeError) as exc:
        errors.append(f"Invalid Unreal project descriptor: {exc}")
        return

    if descriptor.get("EngineAssociation") != "5.6":
        errors.append("FashionRotunda.uproject must target Unreal Engine 5.6")

    modules = descriptor.get("Modules", [])
    if not any(module.get("Name") == "FashionRotunda" for module in modules):
        errors.append("FashionRotunda.uproject does not declare the FashionRotunda module")


def validate_gitignore(errors: list[str]) -> None:
    content = (ROOT / ".gitignore").read_text(encoding="utf-8")
    required_entries = (
        "Binaries/",
        "Content/",
        "DerivedDataCache/",
        "Intermediate/",
        "Saved/",
    )
    for entry in required_entries:
        if entry not in content:
            errors.append(f".gitignore is missing required entry: {entry}")


def validate_paths(paths: list[Path], errors: list[str]) -> None:
    for required in REQUIRED_PATHS:
        if Path(required) not in paths:
            errors.append(f"Required repository file is not tracked: {required}")

    for relative in paths:
        parts = relative.parts
        lower_path = relative.as_posix().lower()

        if relative.name in LOCAL_ONLY_NAMES or any(part in lower_path for part in LOCAL_ONLY_PARTS):
            errors.append("A local-only path is tracked")

        if parts and parts[0] in EXCLUDED_ROOTS:
            errors.append(f"Generated or private path is tracked: {relative.as_posix()}")

        if relative.suffix.lower() in EXCLUDED_SUFFIXES:
            errors.append(f"Generated artifact is tracked: {relative.as_posix()}")

        absolute = ROOT / relative
        if absolute.exists() and absolute.stat().st_size > MAX_FILE_BYTES:
            errors.append(f"Tracked file exceeds 10 MiB: {relative.as_posix()}")


def validate_text(paths: list[Path], errors: list[str]) -> None:
    for relative in paths:
        absolute = ROOT / relative
        if not absolute.is_file():
            continue

        data = absolute.read_bytes()
        if is_probably_binary(data):
            continue

        text = data.decode("utf-8", errors="replace")
        lowered = text.lower()

        if any(phrase in lowered for phrase in LOCAL_ONLY_PHRASES):
            errors.append(f"Public file contains local-only publication metadata: {relative.as_posix()}")

        for pattern in SECRET_PATTERNS:
            if pattern.search(text):
                errors.append(f"Potential credential detected: {relative.as_posix()}")
                break


def main() -> int:
    errors: list[str] = []

    try:
        paths = tracked_paths()
    except (OSError, subprocess.CalledProcessError) as exc:
        print(f"Unable to enumerate tracked files: {exc}", file=sys.stderr)
        return 2

    validate_descriptor(errors)
    validate_gitignore(errors)
    validate_paths(paths, errors)
    validate_text(paths, errors)

    if errors:
        print("Repository validation failed:")
        for error in sorted(set(errors)):
            print(f"- {error}")
        return 1

    print(f"Repository validation passed for {len(paths)} tracked files.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
