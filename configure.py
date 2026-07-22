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
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
    "-cwd source"
]

cflags_zlib = [
    "-nodefaults",
    "-proc generic",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,p",
    "-str reuse",
    "-inline on",
    "-maxerrors 1",
    "-nosyspath",
    # for multibyte
    "-multibyte",
    # includes and defines
    "-i include",
    "-i src/dolsdk2004/include",
    "-i src/dolsdk2004/include/libc",
    "-i src/zlib",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
]

cflags_libpng = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-fp_contract on",
    "-Cpp_exceptions off",
    "-O4,p",
    "-str reuse",
    "-inline on",
    "-maxerrors 1",
    "-nosyspath",
    # for multibyte
    "-multibyte",
    # includes and defines
    "-cwd source",
    "-i include",
    "-i src/zlib",
    "-i include/PowerPC_EABI_Support/MSL_C/",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
    "-DPNG_NO_WRITE_tIME",
    "-DPNG_USER_MEM_SUPPORTED",
    "-DPNG_WRITE_tIME_SUPPORTED",
    "-DPNG_NO_WRITE_iCCP",
    "-DPNG_SETJMP_NOT_SUPPORTED",
    "-DPNG_NO_READ_iCCP",
    "-DPNG_NO_PROGRESSIVE_READ",
    "-DPNG_PROGRESSIVE_READ_NOT_SUPPORTED",
    "-DPNG_READ_BIG_ENDIAN_SUPPORTED",
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

cflags_dolsdk= [
    *cflags_base,
    "-i src/dolsdk2004/include",
    "-i src/dolsdk2004/include/dolphin",
    "-i src/dolsdk2004/include/libc",
]

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
    "-i include/PowerPC_EABI_Support/MSL_C/",
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
        "src_dir": "src",
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

# Helper function for zlib
def Library(lib_name: str, mw_version, cflags: Any, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": mw_version,
        "cflags": cflags,
        "progress_category": lib_name,
        "src_dir": "src",
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
            *cflags_dolsdk,
            "-i src/dolsdk2004/src",
            "-i src/dolsdk2004/src/card",
            "-i src/dolsdk2004/src/os",
        ],
        [
            Object(Matching,"dolsdk2004/src/card/CARDCheck.c",),
            Object(Matching,"dolsdk2004/src/card/CARDRdwr.c",),
            Object(Matching,"dolsdk2004/src/card/CARDBlock.c",),
            Object(Matching,"dolsdk2004/src/card/CARDDir.c",),
            Object(Matching,"dolsdk2004/src/card/CARDMount.c",),
            Object(Matching,"dolsdk2004/src/card/CARDFormat.c",),
            Object(Matching,"dolsdk2004/src/card/CARDOpen.c",),
            Object(Matching,"dolsdk2004/src/card/CARDCreate.c",),
            Object(Matching,"dolsdk2004/src/card/CARDRead.c",),
            Object(Matching,"dolsdk2004/src/card/CARDWrite.c",),
            Object(Matching,"dolsdk2004/src/card/CARDDelete.c",),
            Object(Matching,"dolsdk2004/src/card/CARDStat.c",),
            Object(Matching,"dolsdk2004/src/card/CARDUnlock.c",),
            Object(Matching,"dolsdk2004/src/card/CARDBios.c",),
        ],
    ),
    DolphinLib(
        "si",
        [
            *cflags_dolsdk,
            "-i src/dolsdk2004/src/os",
        ],
        [
            Object(Matching,"dolsdk2004/src/si/SIBios.c",),
            Object(Matching,"dolsdk2004/src/si/SISamplingRate.c",),
        ],
    ),
    DolphinLib(
        "exi",
        [
            *cflags_dolsdk,
            "-i src/dolsdk2004/src/os",
        ],
        [
            Object(Matching,"dolsdk2004/src/exi/EXIBios.c",cflags=[x for x in cflags_dolsdk if x != "-O4,p"] + ["-O3,p", "-DDOLPHIN_SDK"],),
            Object(Matching,"dolsdk2004/src/exi/EXIUart.c",),
        ],
    ),
    DolphinLib(
        "mix",
        cflags_dolsdk,
        [
            Object(Matching,"dolsdk2004/src/mix/mix.c",),
        ],
    ),
    DolphinLib(
        "mtx",
        cflags_dolsdk,
        [
            Object(Matching,"dolsdk2004/src/mtx/mtx.c",),
        ],
    ),
    DolphinLib(
        "os",
        [
            *cflags_dolsdk,
            "-D__GEKKO__",
            "-i src/dolsdk2004/src/os",
            "-i src/dolsdk2004/src/dvd",
        ],
        [
            Object(Matching,"dolsdk2004/src/os/OS.c",),
            Object(Matching,"dolsdk2004/src/os/OSAlarm.c",),
            Object(NonMatching,"dolsdk2004/src/os/OSAlloc.c",),
            Object(Matching,"dolsdk2004/src/os/OSArena.c",),
            Object(Matching,"dolsdk2004/src/os/OSAudioSystem.c",),
            Object(Matching,"dolsdk2004/src/os/OSCache.c",),
            Object(Matching,"dolsdk2004/src/os/OSContext.c",),
            Object(Matching,"dolsdk2004/src/os/OSError.c",),
            Object(Matching,"dolsdk2004/src/os/OSExec.c",),
            Object(Matching,"dolsdk2004/src/os/OSFont.c",),
            Object(Matching,"dolsdk2004/src/os/OSInterrupt.c",),
            Object(Matching,"dolsdk2004/src/os/OSLink.c",),
            Object(Matching,"dolsdk2004/src/os/OSMemory.c",),
            Object(Matching,"dolsdk2004/src/os/OSMutex.c",),
            Object(Matching,"dolsdk2004/src/os/OSReboot.c",),
            Object(Matching,"dolsdk2004/src/os/OSReset.c",),
            Object(Matching,"dolsdk2004/src/os/OSResetSW.c",),
            Object(NonMatching,"dolsdk2004/src/os/OSRtc.c",),
            Object(NonMatching,"dolsdk2004/src/os/OSSync.c",),
            Object(Matching,"dolsdk2004/src/os/OSThread.c",),
            Object(Matching,"dolsdk2004/src/os/OSTime.c",),
            Object(Matching,"dolsdk2004/src/os/__ppc_eabi_init.c",),
        ],
    ),
    DolphinLib(
        "pad",
        [*cflags_dolsdk, "-i src/dolsdk2004/src/si"],
        [
            Object(Matching, "dolsdk2004/src/pad/Padclamp.c"),
            Object(Matching, "dolsdk2004/src/pad/Pad.c"),
        ],
    ),
    DolphinLib(
        "vi",
        [
            *cflags_dolsdk,
            "-i src/dolsdk2004/src/gx",
            "-i src/dolsdk2004/src/os",
            "-i src/dolsdk2004/src/vi",
        ],
        [
            Object(Matching, "dolsdk2004/src/vi/vi.c"),
        ],
    ),
    DolphinLib(
        "base",
        cflags_dolsdk,
        [
            Object(Matching, "dolsdk2004/src/base/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "axart",
        cflags_dolsdk,
        [
            Object(Matching, "dolsdk2004/src/axart/axart.c"),
            Object(NonMatching, "dolsdk2004/src/axart/axartlfo.c",cflags=[x for x in cflags_dolsdk if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(Matching, "dolsdk2004/src/axart/axartlpf.c"),
            Object(Matching, "dolsdk2004/src/axart/axart3d.c",cflags=[x for x in cflags_dolsdk if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(Matching, "dolsdk2004/src/axart/axartenv.c"),
            Object(Matching, "dolsdk2004/src/axart/axartsound.c"),
            Object(Matching, "dolsdk2004/src/axart/axartcents.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [*cflags_dolsdk, "-i src/dolsdk2004/src/gx",],
        [
            Object(Matching, "dolsdk2004/src/gx/GXPerf.c"),
            Object(Matching, "dolsdk2004/src/gx/GXTransform.c",cflags=[x for x in cflags_dolsdk if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(Matching, "dolsdk2004/src/gx/GXDisplayList.c"),
            Object(Matching, "dolsdk2004/src/gx/GXPixel.c"),
            Object(Matching, "dolsdk2004/src/gx/GXTev.c"),
            Object(Matching, "dolsdk2004/src/gx/GXBump.c"),
            Object(Matching, "dolsdk2004/src/gx/GXTexture.c"),
            Object(Matching, "dolsdk2004/src/gx/GXLight.c",cflags=[x for x in cflags_dolsdk if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(Matching, "dolsdk2004/src/gx/GXFrameBuf.c"),
            Object(Matching, "dolsdk2004/src/gx/GXGeometry.c"),
            Object(Matching, "dolsdk2004/src/gx/GXMisc.c"),
            Object(Matching, "dolsdk2004/src/gx/GXAttr.c"),
            Object(Matching, "dolsdk2004/src/gx/GXFifo.c"),
            Object(Matching, "dolsdk2004/src/gx/GXInit.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            *cflags_dolsdk,
            "-i src/dolsdk2004/src/dvd",
            "-i src/dolsdk2004/src/os",
        ],
        [
            Object(Matching, "dolsdk2004/src/dvd/fstload.c"),
            Object(Matching, "dolsdk2004/src/dvd/dvdFatal.c"),
            Object(Matching, "dolsdk2004/src/dvd/dvdidutils.c"),
            Object(Matching, "dolsdk2004/src/dvd/dvderror.c"),
            Object(Matching, "dolsdk2004/src/dvd/dvdqueue.c"),
            Object(Matching, "dolsdk2004/src/dvd/dvd.c"),
            Object(Matching, "dolsdk2004/src/dvd/dvdfs.c"),
            Object(NonMatching, "dolsdk2004/src/dvd/dvdlow.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            *cflags_dolsdk,
            "-i src/dolsdk2004/src/dsp",
        ],
        [
            Object(Matching, "dolsdk2004/src/dsp/dsp_task.c"),
            Object(Matching, "dolsdk2004/src/dsp/dsp_debug.c"),
            Object(Matching, "dolsdk2004/src/dsp/dsp.c"),
        ],
    ),
    DolphinLib(
        "db",
        cflags_dolsdk,
        [
            Object(Matching, "dolsdk2004/src/db/db.c"),
        ],
    ),
    DolphinLib(
        "axfx",
        [
            *cflags_dolsdk,
            "-i src/dolsdk2004/src/axfx",
        ],
        [
            Object(Matching, "dolsdk2004/src/axfx/chorus.c"),  
            Object(Matching, "dolsdk2004/src/axfx/reverb_hi_4ch.c",cflags=[x for x in cflags_dolsdk if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(Matching, "dolsdk2004/src/axfx/delay.c"),
            Object(Matching, "dolsdk2004/src/axfx/axfx.c"),
            Object(NonMatching, "dolsdk2004/src/axfx/reverb_std.c",cflags=[x for x in cflags_dolsdk if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(NonMatching, "dolsdk2004/src/axfx/reverb_hi.c",cflags=[x for x in cflags_dolsdk if x != "-fp_contract on"] + ["-fp_contract off"],),
        ],
    ),
    DolphinLib(
        "ar",
        cflags_dolsdk,
        [
            Object(Matching, "dolsdk2004/src/ar/arq.c"),
            Object(Matching, "dolsdk2004/src/ar/ar.c"),
        ],
    ),
    DolphinLib(
        "ax",
        cflags_dolsdk,
        [
            Object(Matching, "dolsdk2004/src/ax/AXProf.c"),
            Object(Matching, "dolsdk2004/src/ax/AXVPB.c"),
            Object(Matching, "dolsdk2004/src/ax/AXSPB.c"),
            Object(Matching, "dolsdk2004/src/ax/AXOut.c"),
            Object(Matching, "dolsdk2004/src/ax/AXCL.c"),
            Object(Matching, "dolsdk2004/src/ax/AXAux.c"),
            Object(Matching, "dolsdk2004/src/ax/AXAlloc.c"),
            Object(Matching, "dolsdk2004/src/ax/AX.c"),
        ],
    ),
    DolphinLib(
        "amcstubs",
        cflags_dolsdk,
        [
            Object(Matching, "dolsdk2004/src/amcstubs/AmcExi2Stubs.c"),
        ],
    ),
    DolphinLib(
        "ai",
        [*cflags_dolsdk, "-i src/dolsdk2004/src/gx",],
        [
            Object(Matching, "dolsdk2004/src/ai/ai.c"),
        ],
    ),
    DolphinLib(
        "cflags_dolsdk",
        cflags_dolsdk,
        [
            Object(NonMatching, "dolsdk2004/src/odenotstub/odenotstub.c"),
        ],
    ),
    Library(
        "zlib",
        "GC/1.3",
        cflags_zlib,
        [
            Object(Matching, "zlib/zutil.c"),
            Object(Matching, "zlib/trees.c"),
            Object(Matching, "zlib/infutil.c"),
            Object(Matching, "zlib/inftrees.c"),
            Object(Matching, "zlib/inflate.c"),
            Object(Matching, "zlib/inffast.c"),
            Object(Matching, "zlib/infcodes.c"),
            Object(Matching, "zlib/infblock.c"),
            Object(Matching, "zlib/deflate.c"),
            Object(Matching, "zlib/crc32.c"),
            Object(Matching, "zlib/adler32.c"),
        ],
    ),
    Library(
        "libpng",
        "GC/1.3.2r",
        cflags_libpng,
        [
            Object(Matching, "libpng/pngwutil.c",),
            Object(Matching, "libpng/pngwtran.c"),
            Object(Matching, "libpng/pngwrite.c"),
            Object(Matching, "libpng/pngwio.c"),
            Object(Matching, "libpng/pngtrans.c"),
            Object(Matching, "libpng/pngset.c"),
            Object(Matching, "libpng/pngrutil.c"),
            Object(Matching, "libpng/pngrtran.c"),
            Object(Matching, "libpng/pngrio.c"),
            Object(Matching, "libpng/pngread.c"),
            Object(Matching, "libpng/pngmem.c"),
            Object(Matching, "libpng/pngget.c"),
            Object(Matching, "libpng/pngerror.c"),
            Object(Matching, "libpng/png.c"),
        ],
    ),
    Library(
        "MSL",
        "GC/1.3.2r",
        cflags_runtime,
        [
            Object(Matching,"Runtime\MSL\Math\k_rem_pio2.c"),
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
    ProgressCategory("MSL", "MSL"),
    ProgressCategory("zlib", "zlib"),
    ProgressCategory("libpng", "libpng"),
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
