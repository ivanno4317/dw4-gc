Regarding AI use
--------
The goal of decompilation is to obtain the game’s source code in a human-readable format.
If you wish to fork the repository to continue the work using AI and agents, please feel free to contact me directly on Discord so that I can assist you personally and provide further information on how best to achieve this goal.

https://discord.com/users/286968262858637312

I repeat, the goal is to obtain high-quality, human-readable code.

I do not support Slopcomps in any way.

Do not fork the repository if you are delegating work to agents without knowing how decompilation works, how to use tools such as Ghidra and IDA, or how dtk-template works.

dw4-gc  
=============

A work-in-progress decompilation of Digimon World 4.

This repository does **not** contain any game assets or assembly whatsoever. An existing copy of the game is required.

Supported versions:

- `GDJEB2`: Rev 1 (USA)

Dependencies
============

Windows
--------

On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.  
When running under WSL, [objdiff](#diffing) is unable to get filesystem notifications for automatic rebuilds.

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

macOS
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):

  ```sh
  brew install ninja
  ```

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Linux
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Building
========

- Clone the repository:

  ```sh
  git clone https://github.com/my/repo.git
  ```

- Copy your game's disc image to `orig/GDJEB2`.
  - Supported formats: ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ, TGC
  - After the initial build, the disc image can be deleted to save space.

- Configure:

  ```sh
  python configure.py
  ```

  To use a version other than `GDJEB2` (USA), specify it with `--version`.

- Build:

  ```sh
  ninja
  ```

Diffing
=======

Once the initial build succeeds, an `objdiff.json` should exist in the project root.

Download the latest release from [encounter/objdiff](https://github.com/encounter/objdiff). Under project settings, set `Project directory`. The configuration should be loaded automatically.

Select an object from the left sidebar to begin diffing. Changes to the project will rebuild automatically: changes to source files, headers, `configure.py`, `splits.txt` or `symbols.txt`.


Progress
=======

Thanks for checking out the project!

Please keep in mind that progress might be a bit periodic right now as I’m currently balancing development with my university studies and mental health. I’m working on it whenever I get a chance.

Contributions, feedback, and pull requests are always welcome!
