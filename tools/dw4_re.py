"""Reusable helpers for manually reverse-engineering DW4's main.dol: listing
candidate functions, disassembling raw words, resolving branch targets, and
converting file offsets <-> virtual addresses. Not part of the ninja build --
a standalone analysis aid for finding the next function(s) to match.
"""
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DOL_PATH = ROOT / "build/GDJEB2/main.dol"
SYMBOLS_PATH = ROOT / "config/GDJEB2/symbols.txt"
SPLITS_PATH = ROOT / "config/GDJEB2/splits.txt"

SECTIONS = [
    # name, address, file_off, size
    (".init", 0x80003100, 0x100, 0x24E8),
    ("extab", 0x80005600, 0x3F5300, 0xD590),
    ("extabindex", 0x80012BA0, 0x4028A0, 0xD5A4),
    (".text", 0x80020160, 0x2600, 0x3F2CEC),
    (".ctors", 0x80412E60, 0x40FE60, 0x40),
    (".dtors", 0x80412EA0, 0x40FEA0, 0x10),
    (".rodata", 0x80412EC0, 0x40FEC0, 0x50234),
    (".data", 0x80463100, 0x460100, 0x8F06C),
    (".sdata", 0x8055CF00, 0x4EF180, 0x4574),
    (".sdata2", 0x80566220, 0x4F3700, 0x13C1),
]


def load_dol():
    return DOL_PATH.read_bytes()


def va_to_off(va):
    for name, addr, off, size in SECTIONS:
        if addr <= va < addr + size:
            return off + (va - addr)
    return None


def off_to_va(off):
    for name, addr, sec_off, size in SECTIONS:
        if sec_off <= off < sec_off + size:
            return addr + (off - sec_off)
    return None


def words_at(data, va, n):
    off = va_to_off(va)
    return struct.unpack_from(f">{n}I", data, off)


def bl_target(pc, word):
    op = word >> 26
    if op != 18:
        return None
    off = word & 0x03FFFFFC
    if off & 0x02000000:
        off -= 0x04000000
    aa = (word >> 1) & 1
    return off if aa else pc + off


def find_string(data, s):
    """Return all file offsets where the given string appears null-terminated."""
    needle = s.encode() + b"\x00"
    out = []
    start = 0
    while True:
        idx = data.find(needle, start)
        if idx == -1:
            break
        out.append(idx)
        start = idx + 1
    return out


def find_callers(data, target_va, text_only=True):
    """Scan .text for b/bl instructions branching to target_va."""
    text_addr, text_off, text_size = 0x80020160, 0x2600, 0x3F2CEC
    words = struct.unpack_from(f">{text_size // 4}I", data, text_off)
    hits = []
    for i, w in enumerate(words):
        t = bl_target(text_addr + i * 4, w)
        if t == target_va:
            hits.append((text_addr + i * 4, bool(w & 1)))
    return hits


def load_symbols():
    """Returns list of (name, addr, size) for type:function entries."""
    out = []
    pat = re.compile(r"^(\S+) = \.text:0x([0-9A-Fa-f]+); // type:function size:0x([0-9A-Fa-f]+)")
    for line in SYMBOLS_PATH.read_text().splitlines():
        m = pat.match(line)
        if m:
            out.append((m.group(1), int(m.group(2), 16), int(m.group(3), 16)))
    return out


def load_claimed_ranges():
    """Returns list of (start, end, filename) for .text splits already claimed."""
    claimed = []
    cur_file = None
    pat = re.compile(r"\t(\S+)\s+start:0x([0-9A-Fa-f]+) end:0x([0-9A-Fa-f]+)")
    for line in SPLITS_PATH.read_text().splitlines():
        if line and not line.startswith("\t") and line.endswith(":"):
            cur_file = line[:-1]
            continue
        m = pat.match(line)
        if m and m.group(1) == ".text":
            claimed.append((int(m.group(2), 16), int(m.group(3), 16), cur_file))
    return claimed


def is_claimed(addr, claimed):
    for s, e, f in claimed:
        if s <= addr < e:
            return f
    return None


def list_candidates(min_size=0, max_size=0x40, limit=60):
    """Named, unclaimed functions, sorted by size ascending -- good next targets."""
    claimed = load_claimed_ranges()
    syms = load_symbols()
    out = []
    for name, addr, size in syms:
        if name.startswith(("fn_", "@", "dtor_")):
            continue
        if not (min_size <= size <= max_size):
            continue
        if is_claimed(addr, claimed):
            continue
        out.append((size, addr, name))
    out.sort()
    return out[:limit]


def disasm_words(data, addr, size):
    n = size // 4
    ws = words_at(data, addr, n)
    return [(addr + i * 4, w) for i, w in enumerate(ws)]


if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else "candidates"
    data = load_dol()
    if cmd == "candidates":
        max_size = int(sys.argv[2], 0) if len(sys.argv) > 2 else 0x40
        for size, addr, name in list_candidates(max_size=max_size):
            print(f"{addr:#010x} {size:#x} {name}")
    elif cmd == "dump":
        addr = int(sys.argv[2], 0)
        size = int(sys.argv[3], 0)
        for a, w in disasm_words(data, addr, size):
            print(f"{a:#010x} {w:#010x}")
    elif cmd == "callers":
        target = int(sys.argv[2], 0)
        for src, lk in find_callers(data, target):
            print(f"{src:#010x} {'bl' if lk else 'b'}")
    elif cmd == "sym":
        addr = int(sys.argv[2], 0)
        for name, a, size in load_symbols():
            if a == addr:
                print(name, hex(size))
