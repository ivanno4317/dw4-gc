#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "GDJEB2",  # 0
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--ninja",
    metavar="BINARY",
    type=Path,
    help="path to ninja binary (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--warn",
    dest="warn",
    type=str,
    choices=["all", "off", "error"],
    help="how to handle warnings",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-2"
config.compilers_tag = "20251118"
config.dtk_tag = "v1.8.3"
config.objdiff_tag = "v3.6.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.3"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    # define the platform
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    # for multibyte
    "-multibyte",
    # includes and defines
    "-i include",
    "-i libs/dolsdk2004/include",
    "-i libs/dolsdk2004/include/libc",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
    "-cwd source"
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Warning flags
if args.warn == "all":
    cflags_base.append("-W all")
elif args.warn == "off":
    cflags_base.append("-W off")
elif args.warn == "error":
    cflags_base.append("-W error")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
]

# REL flags
cflags_rel = [
    *cflags_base,
    "-sdata 0",
    "-sdata2 0",
]

config.linker_version = "GC/1.3.2"


# Helper function for Dolphin libraries
def DolphinLib(lib_name: str, cflags: Any, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": [*cflags, "-DDOLPHIN_SDK"],
        "progress_category": "sdk",
        "src_dir": "libs/dolsdk2004/src",
        "objects": objects,
    }


# Helper function for REL script objects
def Rel(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3.2",
        "cflags": cflags_rel,
        "progress_category": "game",
        "objects": objects,
    }


Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "sdk",  # str | List[str]
        "objects": [
            Object(NonMatching, "Runtime.PPCEABI.H/global_destructor_chain.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
        ],        
    },
    DolphinLib(
        "card",
        [
            *cflags_base,
            "-i libs/dolsdk2004/src",
            "-i libs/dolsdk2004/src/card",
            "-i libs/dolsdk2004/src/os",
        ],
        [
            Object(Matching,"card/CARDCheck.c",),
            Object(Matching,"card/CARDRdwr.c",),
            Object(Matching,"card/CARDBlock.c",),
            Object(Matching,"card/CARDDir.c",),
            Object(Matching,"card/CARDMount.c",),
            Object(Matching,"card/CARDFormat.c",),
            Object(Matching,"card/CARDOpen.c",),
            Object(Matching,"card/CARDCreate.c",),
            Object(Matching,"card/CARDRead.c",),
            Object(Matching,"card/CARDWrite.c",),
            Object(Matching,"card/CARDDelete.c",),
            Object(Matching,"card/CARDStat.c",),
            Object(Matching,"card/CARDUnlock.c",),
            Object(Matching,"card/CARDBios.c",),
        ],
    ),
    DolphinLib(
        "si",
        [
            *cflags_base,
            "-i libs/dolsdk2004/src/os",
        ],
        [
            Object(Matching,"si/SIBios.c",),
            Object(Matching,"si/SISamplingRate.c",),
        ],
    ),
    DolphinLib(
        "exi",
        [
            *cflags_base,
            "-i libs/dolsdk2004/src/os",
        ],
        [
            Object(Matching,"exi/EXIBios.c",cflags=[x for x in cflags_base if x != "-O4,p"] + ["-O3,p", "-DDOLPHIN_SDK"],),
            Object(Matching,"exi/EXIUart.c",),
        ],
    ),
    DolphinLib(
        "mix",
        cflags_base,
        [
            Object(Matching,"mix/mix.c",),
        ],
    ),
    DolphinLib(
        "mtx",
        cflags_base,
        [
            Object(Matching,"mtx/mtx.c",),
        ],
    ),
    DolphinLib(
        "os",
        [
            *cflags_base,
            "-D__GEKKO__",
            "-i libs/dolsdk2004/src/os",
            "-i libs/dolsdk2004/src/dvd",
        ],
        [
            Object(Matching,"os/OS.c",),
            Object(Matching,"os/OSAlarm.c",),
            Object(NonMatching,"os/OSAlloc.c",),
            Object(Matching,"os/OSArena.c",),
            Object(Matching,"os/OSAudioSystem.c",),
            Object(Matching,"os/OSCache.c",),
            Object(Matching,"os/OSContext.c",),
            Object(Matching,"os/OSError.c",),
            Object(Matching,"os/OSExec.c",),
            Object(Matching,"os/OSFont.c",),
            Object(Matching,"os/OSInterrupt.c",),
            Object(Matching,"os/OSLink.c",),
            Object(Matching,"os/OSMemory.c",),
            Object(Matching,"os/OSMutex.c",),
            Object(Matching,"os/OSReboot.c",),
            Object(Matching,"os/OSReset.c",),
            Object(Matching,"os/OSResetSW.c",),
            Object(NonMatching,"os/OSRtc.c",),
            Object(NonMatching,"os/OSSync.c",),
            Object(Matching,"os/OSThread.c",),
            Object(Matching,"os/OSTime.c",),
            Object(Matching,"os/__ppc_eabi_init.c",),
        ],
    ),
    DolphinLib(
        "pad",
        [*cflags_base, "-i libs/dolsdk2004/src/si"],
        [
            Object(Matching, "pad/Padclamp.c"),
            Object(Matching, "pad/Pad.c"),
        ],
    ),
    DolphinLib(
        "vi",
        [
            *cflags_base,
            "-i libs/dolsdk2004/src/gx",
            "-i libs/dolsdk2004/src/os",
            "-i libs/dolsdk2004/src/vi",
        ],
        [
            Object(Matching, "vi/vi.c"),
        ],
    ),
    DolphinLib(
        "base",
        cflags_base,
        [
            Object(Matching, "base/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "axart",
        [*cflags_base,],
        [
            Object(Matching, "axart/axart.c"),
            Object(NonMatching, "axart/axartlfo.c",cflags=[x for x in cflags_base if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(Matching, "axart/axartlpf.c"),
            Object(Matching, "axart/axart3d.c",cflags=[x for x in cflags_base if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(Matching, "axart/axartenv.c"),
            Object(Matching, "axart/axartsound.c"),
            Object(Matching, "axart/axartcents.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [*cflags_base, "-i libs/dolsdk2004/src/gx",],
        [
            Object(Matching, "gx/GXPerf.c"),
            Object(Matching, "gx/GXTransform.c",cflags=[x for x in cflags_base if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(Matching, "gx/GXDisplayList.c"),
            Object(Matching, "gx/GXPixel.c"),
            Object(Matching, "gx/GXTev.c"),
            Object(Matching, "gx/GXBump.c"),
            Object(Matching, "gx/GXTexture.c"),
            Object(Matching, "gx/GXLight.c",cflags=[x for x in cflags_base if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(Matching, "gx/GXFrameBuf.c"),
            Object(Matching, "gx/GXGeometry.c"),
            Object(Matching, "gx/GXMisc.c"),
            Object(Matching, "gx/GXAttr.c"),
            Object(Matching, "gx/GXFifo.c"),
            Object(Matching, "gx/GXInit.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            *cflags_base,
            "-i libs/dolsdk2004/src/dvd",
            "-i libs/dolsdk2004/src/os",
        ],
        [
            Object(Matching, "dvd/fstload.c"),
            Object(Matching, "dvd/dvdFatal.c"),
            Object(Matching, "dvd/dvdidutils.c"),
            Object(Matching, "dvd/dvderror.c"),
            Object(Matching, "dvd/dvdqueue.c"),
            Object(Matching, "dvd/dvd.c"),
            Object(Matching, "dvd/dvdfs.c"),
            Object(NonMatching, "dvd/dvdlow.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            *cflags_base,
            "-i libs/dolsdk2004/src/dsp",
        ],
        [
            Object(Matching, "dsp/dsp_task.c"),
            Object(Matching, "dsp/dsp_debug.c"),
            Object(Matching, "dsp/dsp.c"),
        ],
    ),
    DolphinLib(
        "db",
        cflags_base,
        [
            Object(Matching, "db/db.c"),
        ],
    ),
    DolphinLib(
        "axfx",
        [
            *cflags_base,
            "-i libs/dolsdk2004/src/axfx",
        ],
        [
            Object(Matching, "axfx/chorus.c"),  
            Object(Matching, "axfx/reverb_hi_4ch.c",cflags=[x for x in cflags_base if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(Matching, "axfx/delay.c"),
            Object(Matching, "axfx/axfx.c"),
            Object(NonMatching, "axfx/reverb_std.c",cflags=[x for x in cflags_base if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(NonMatching, "axfx/reverb_hi.c",cflags=[x for x in cflags_base if x != "-fp_contract on"] + ["-fp_contract off"],),
        ],
    ),
    DolphinLib(
        "ar",
        cflags_base,
        [
            Object(Matching, "ar/arq.c"),
            Object(Matching, "ar/ar.c"),
        ],
    ),
    DolphinLib(
        "ax",
        cflags_base,
        [
            Object(Matching, "ax/AXProf.c"),
            Object(Matching, "ax/AXVPB.c"),
            Object(Matching, "ax/AXSPB.c"),
        ],
    ),
    DolphinLib(
        "ai",
        [*cflags_base, "-i libs/dolsdk2004/src/gx",],
        [
            Object(NonMatching, "ai/ai.c"),
        ],
    ),
]


# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects


# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("sdk", "SDK Code"),
]
config.progress_each_module = args.verbose
# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    # Marks relocations as mismatching if the target value is different
    # Default is "functionRelocDiffs=none", which is most lenient
    # "--config functionRelocDiffs=data_value",
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
