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
    "-i include/dolsdk2004/",
    "-i include/dolsdk2004/libc",
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
    "-i include/dolsdk2004/",
    "-i include/dolsdk2004/dolphin",
    "-i include/dolsdk2004/libc",
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
    "-i src/dolsdk2004/",
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
            "-i src/dolsdk2004",
            "-i src/dolsdk2004/card",
            "-i src/dolsdk2004/os",
        ],
        [
            Object(Matching,"dolsdk2004/card/CARDCheck.c",),
            Object(Matching,"dolsdk2004/card/CARDRdwr.c",),
            Object(Matching,"dolsdk2004/card/CARDBlock.c",),
            Object(Matching,"dolsdk2004/card/CARDDir.c",),
            Object(Matching,"dolsdk2004/card/CARDMount.c",),
            Object(Matching,"dolsdk2004/card/CARDFormat.c",),
            Object(Matching,"dolsdk2004/card/CARDOpen.c",),
            Object(Matching,"dolsdk2004/card/CARDCreate.c",),
            Object(Matching,"dolsdk2004/card/CARDRead.c",),
            Object(Matching,"dolsdk2004/card/CARDWrite.c",),
            Object(Matching,"dolsdk2004/card/CARDDelete.c",),
            Object(Matching,"dolsdk2004/card/CARDStat.c",),
            Object(Matching,"dolsdk2004/card/CARDUnlock.c",),
            Object(Matching,"dolsdk2004/card/CARDBios.c",),
        ],
    ),
    DolphinLib(
        "si",
        [
            *cflags_dolsdk,
            "-i src/dolsdk2004/os",
        ],
        [
            Object(Matching,"dolsdk2004/si/SIBios.c",),
            Object(Matching,"dolsdk2004/si/SISamplingRate.c",),
        ],
    ),
    DolphinLib(
        "exi",
        [
            *cflags_dolsdk,
            "-i src/dolsdk2004/os",
        ],
        [
            Object(Matching,"dolsdk2004/exi/EXIBios.c",cflags=[x for x in cflags_dolsdk if x != "-O4,p"] + ["-O3,p", "-DDOLPHIN_SDK"],),
            Object(Matching,"dolsdk2004/exi/EXIUart.c",),
        ],
    ),
    DolphinLib(
        "mix",
        cflags_dolsdk,
        [
            Object(Matching,"dolsdk2004/mix/mix.c",),
        ],
    ),
    DolphinLib(
        "mtx",
        cflags_dolsdk,
        [
            Object(Matching,"dolsdk2004/mtx/mtx.c",),
        ],
    ),
    DolphinLib(
        "os",
        [
            *cflags_dolsdk,
            "-D__GEKKO__",
            "-i src/dolsdk2004/os",
            "-i src/dolsdk2004/dvd",
        ],
        [
            Object(Matching,"dolsdk2004/os/OS.c",),
            Object(Matching,"dolsdk2004/os/OSAlarm.c",),
            Object(NonMatching,"dolsdk2004/os/OSAlloc.c",),
            Object(Matching,"dolsdk2004/os/OSArena.c",),
            Object(Matching,"dolsdk2004/os/OSAudioSystem.c",),
            Object(Matching,"dolsdk2004/os/OSCache.c",),
            Object(Matching,"dolsdk2004/os/OSContext.c",),
            Object(Matching,"dolsdk2004/os/OSError.c",),
            Object(Matching,"dolsdk2004/os/OSExec.c",),
            Object(Matching,"dolsdk2004/os/OSFont.c",),
            Object(Matching,"dolsdk2004/os/OSInterrupt.c",),
            Object(Matching,"dolsdk2004/os/OSLink.c",),
            Object(Matching,"dolsdk2004/os/OSMemory.c",),
            Object(Matching,"dolsdk2004/os/OSMutex.c",),
            Object(Matching,"dolsdk2004/os/OSReboot.c",),
            Object(Matching,"dolsdk2004/os/OSReset.c",),
            Object(Matching,"dolsdk2004/os/OSResetSW.c",),
            Object(NonMatching,"dolsdk2004/os/OSRtc.c",),
            Object(NonMatching,"dolsdk2004/os/OSSync.c",),
            Object(Matching,"dolsdk2004/os/OSThread.c",),
            Object(Matching,"dolsdk2004/os/OSTime.c",),
            Object(Matching,"dolsdk2004/os/__ppc_eabi_init.c",),
        ],
    ),
    DolphinLib(
        "pad",
        [*cflags_dolsdk, "-i src/dolsdk2004/si"],
        [
            Object(Matching, "dolsdk2004/pad/Padclamp.c"),
            Object(Matching, "dolsdk2004/pad/Pad.c"),
        ],
    ),
    DolphinLib(
        "vi",
        [
            *cflags_dolsdk,
            "-i src/dolsdk2004/gx",
            "-i src/dolsdk2004/os",
            "-i src/dolsdk2004/vi",
        ],
        [
            Object(Matching, "dolsdk2004/vi/vi.c"),
        ],
    ),
    DolphinLib(
        "base",
        cflags_dolsdk,
        [
            Object(Matching, "dolsdk2004/base/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "axart",
        cflags_dolsdk,
        [
            Object(Matching, "dolsdk2004/axart/axart.c"),
            Object(NonMatching, "dolsdk2004/axart/axartlfo.c",cflags=[x for x in cflags_dolsdk if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(Matching, "dolsdk2004/axart/axartlpf.c"),
            Object(Matching, "dolsdk2004/axart/axart3d.c",cflags=[x for x in cflags_dolsdk if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(Matching, "dolsdk2004/axart/axartenv.c"),
            Object(Matching, "dolsdk2004/axart/axartsound.c"),
            Object(Matching, "dolsdk2004/axart/axartcents.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [*cflags_dolsdk, "-i src/dolsdk2004/gx",],
        [
            Object(Matching, "dolsdk2004/gx/GXPerf.c"),
            Object(Matching, "dolsdk2004/gx/GXTransform.c",cflags=[x for x in cflags_dolsdk if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(Matching, "dolsdk2004/gx/GXDisplayList.c"),
            Object(Matching, "dolsdk2004/gx/GXPixel.c"),
            Object(Matching, "dolsdk2004/gx/GXTev.c"),
            Object(Matching, "dolsdk2004/gx/GXBump.c"),
            Object(Matching, "dolsdk2004/gx/GXTexture.c"),
            Object(Matching, "dolsdk2004/gx/GXLight.c",cflags=[x for x in cflags_dolsdk if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(Matching, "dolsdk2004/gx/GXFrameBuf.c"),
            Object(Matching, "dolsdk2004/gx/GXGeometry.c"),
            Object(Matching, "dolsdk2004/gx/GXMisc.c"),
            Object(Matching, "dolsdk2004/gx/GXAttr.c"),
            Object(Matching, "dolsdk2004/gx/GXFifo.c"),
            Object(Matching, "dolsdk2004/gx/GXInit.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            *cflags_dolsdk,
            "-i src/dolsdk2004/dvd",
            "-i src/dolsdk2004/os",
        ],
        [
            Object(Matching, "dolsdk2004/dvd/fstload.c"),
            Object(Matching, "dolsdk2004/dvd/dvdFatal.c"),
            Object(Matching, "dolsdk2004/dvd/dvdidutils.c"),
            Object(Matching, "dolsdk2004/dvd/dvderror.c"),
            Object(Matching, "dolsdk2004/dvd/dvdqueue.c"),
            Object(Matching, "dolsdk2004/dvd/dvd.c"),
            Object(Matching, "dolsdk2004/dvd/dvdfs.c"),
            Object(NonMatching, "dolsdk2004/dvd/dvdlow.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            *cflags_dolsdk,
            "-i src/dolsdk2004/dsp",
        ],
        [
            Object(Matching, "dolsdk2004/dsp/dsp_task.c"),
            Object(Matching, "dolsdk2004/dsp/dsp_debug.c"),
            Object(Matching, "dolsdk2004/dsp/dsp.c"),
        ],
    ),
    DolphinLib(
        "db",
        cflags_dolsdk,
        [
            Object(Matching, "dolsdk2004/db/db.c"),
        ],
    ),
    DolphinLib(
        "axfx",
        [
            *cflags_dolsdk,
            "-i src/dolsdk2004/axfx",
        ],
        [
            Object(Matching, "dolsdk2004/axfx/chorus.c"),  
            Object(Matching, "dolsdk2004/axfx/reverb_hi_4ch.c",cflags=[x for x in cflags_dolsdk if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(Matching, "dolsdk2004/axfx/delay.c"),
            Object(Matching, "dolsdk2004/axfx/axfx.c"),
            Object(NonMatching, "dolsdk2004/axfx/reverb_std.c",cflags=[x for x in cflags_dolsdk if x != "-fp_contract on"] + ["-fp_contract off"],),
            Object(NonMatching, "dolsdk2004/axfx/reverb_hi.c",cflags=[x for x in cflags_dolsdk if x != "-fp_contract on"] + ["-fp_contract off"],),
        ],
    ),
    DolphinLib(
        "ar",
        cflags_dolsdk,
        [
            Object(Matching, "dolsdk2004/ar/arq.c"),
            Object(Matching, "dolsdk2004/ar/ar.c"),
        ],
    ),
    DolphinLib(
        "ax",
        cflags_dolsdk,
        [
            Object(Matching, "dolsdk2004/ax/AXProf.c"),
            Object(Matching, "dolsdk2004/ax/AXVPB.c"),
            Object(Matching, "dolsdk2004/ax/AXSPB.c"),
            Object(Matching, "dolsdk2004/ax/AXOut.c"),
            Object(Matching, "dolsdk2004/ax/AXCL.c"),
            Object(Matching, "dolsdk2004/ax/AXAux.c"),
            Object(Matching, "dolsdk2004/ax/AXAlloc.c"),
            Object(Matching, "dolsdk2004/ax/AX.c"),
        ],
    ),
    DolphinLib(
        "amcstubs",
        cflags_dolsdk,
        [
            Object(Matching, "dolsdk2004/amcstubs/AmcExi2Stubs.c"),
        ],
    ),
    DolphinLib(
        "ai",
        [*cflags_dolsdk, "-i src/dolsdk2004/gx",],
        [
            Object(Matching, "dolsdk2004/ai/ai.c"),
        ],
    ),
    DolphinLib(
        "cflags_dolsdk",
        cflags_dolsdk,
        [
            Object(NonMatching, "dolsdk2004/odenotstub/odenotstub.c"),
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
        "GC/1.3.2",
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
        "GC/1.3.2",
        cflags_runtime,
        [
            Object(Matching,"Runtime/MSL/Math/e_acos.c"),
            Object(Matching,"Runtime/MSL/Math/e_asin.c"),
            Object(Matching,"Runtime/MSL/Math/e_atan2.c"),
            Object(Matching,"Runtime/MSL/Math/e_exp.c"),
            Object(Matching,"Runtime/MSL/Math/e_fmod.c"),
            Object(Matching,"Runtime/MSL/Math/e_log.c"),
            Object(Matching,"Runtime/MSL/Math/e_log10.c"),
            Object(Matching,"Runtime/MSL/Math/e_pow.c"),
            Object(Matching,"Runtime/MSL/Math/e_rem_pio2.c"),
            Object(Matching,"Runtime/MSL/Math/k_cos.c"),
            Object(Matching,"Runtime/MSL/Math/k_rem_pio2.c"),
            Object(Matching,"Runtime/MSL/Math/k_sin.c"),
            Object(Matching,"Runtime/MSL/Math/k_tan.c"),
            Object(Matching,"Runtime/MSL/Math/s_atan.c"),
            Object(Matching,"Runtime/MSL/Math/s_ceil.c"),
            Object(Matching,"Runtime/MSL/Math/s_copysign.c"),
            Object(Matching,"Runtime/MSL/Math/s_cos.c"),
            Object(Matching,"Runtime/MSL/Math/s_floor.c"),
            Object(Matching,"Runtime/MSL/Math/s_frexp.c"),
            Object(Matching,"Runtime/MSL/Math/s_ldexp.c"),
            Object(Matching,"Runtime/MSL/Math/s_modf.c"),
            Object(Matching,"Runtime/MSL/Math/s_sin.c"),
            Object(Matching,"Runtime/MSL/Math/s_tan.c"),
            Object(Matching,"Runtime/MSL/Math/w_acos.c"),
            Object(Matching,"Runtime/MSL/Math/w_asin.c"),
            Object(Matching,"Runtime/MSL/Math/w_atan2.c"),
            Object(Matching,"Runtime/MSL/Math/w_exp.c"),
            Object(Matching,"Runtime/MSL/Math/w_fmod.c"),
            Object(Matching,"Runtime/MSL/Math/w_log.c"),
            Object(Matching,"Runtime/MSL/Math/w_log10.c"),
            Object(Matching,"Runtime/MSL/Math/w_pow.c"),
            Object(Matching,"Runtime/MSL/Math/e_sqrt.c"),
            Object(Matching,"Runtime/MSL/math_ppc.c"),
            Object(NonMatching,"Runtime/MSL/Common_Embedded/uart_console_io_gcn.c"),
            Object(Matching,"Runtime/MSL/Common/wchar_io.c"),
            Object(Matching,"Runtime/MSL/Common/strtoul.c"),
            Object(NonMatching,"Runtime/MSL/Common/strtold.c"),
            Object(Matching,"Runtime/MSL/Common/string.c"),
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
