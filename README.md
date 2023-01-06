

# Spyro Gem Redistributer

A mod for the original Spyro the Dragon that shuffles gem values in a level around to other gems in the same level! Come up with any% routes on the fly, knowing where none of the high value gems will be beforehand!

This mod was created using the [psx-modding-toolchain by Redhot](https://github.com/mateusfavarin/psx-modding-toolchain). 

### Features

 -  **Randomly shuffles the gem values around in a level, with the other gem values in the same level**. 
 This doesn't just randomize them, it takes into account the gems that already exist in a level, and just moves them around to other gems! That way, the weighting of each levels gem total should be the same.
 -  **Seeding menu so you can randomize/replay seeds as you wish**.
 -  **Quick Reset to "The Adventure Begins"** by pressing "L1 + L2 + R1 + R2 + Triangle"

## Downloads
#### Main Download
 -  **Download Patch**: Download the main [xdelta patch here](https://github.com/C0mposer/Spyro-1-Gem-Redistributer-Mod/releases/download/beta0.5/spyro1_GemRedistributer.xdelta), then your personal Spyro 1 bin file can be [patched here](https://hack64.net/tools/patcher.php)
 #### Other Downloads
 -  **CUE File**: Some emulators will require you to have a cue file to go along with this bin file, if you need one, you can create a cue for your patched bin [here](https://www.duckstation.org/cue-maker/)

 -  **Popstarter VCD:** To learn about creating a VCD for Popstarter to run this mod on PS2, read [this](https://pastebin.com/YsypFwJS)

## Compiling & Building

1. Compiling this mod requires the [psx-modding-toolchain by Redhot](https://github.com/mateusfavarin/psx-modding-toolchain). 
2. Once you have installed it and its pre-requisites, place the folder [from the source code download](https://github.com/C0mposer/Spyro-1-Gem-Redistributer-Mod/archive/refs/heads/master.zip), into the **/games/** folder of your psx-modding-toolchain directory.
3. Browse to the **/mods/GemRedistributer/** directory, and open the MOD.bat file. From here you should be prompted with multiple options in a command line gui

#### Building BIN/CUE
	
	1. First type 1 then press enter to compile, then, type 1 then press enter again for the NTSC version.
	2. After it has compiled, type 4 then enter for "Build Iso", then, type 1 then press enter for the NTSC version.
	3. After it has built, your bin/cue should be in /build/

#### Generating xdelta patch
	
	1. First type 1 then press enter to compile, then, type 1 then press enter again for the NTSC version.
	6. After it has compiled, type 5 then press enter for "Generate xdetla Patch", then type 1 then press enter for the NTSC version.
	7. After it has built, your xdelta patch should be in /build/
	

## Tools Used In Creation

 - [psx-modding-toolchain by Redhot](https://github.com/mateusfavarin/psx-modding-toolchain) for the automation of compiling C code to MIPS object code targeted for the PS1, and building a bin/cue with the mod files injected correctly.
 - [Bizhawk](https://github.com/TASEmulators/BizHawk) for searching/poking PS1 ram values easily
 - [PCSX-Redux](https://github.com/grumpycoders/pcsx-redux/) for hot-reloading mods in for quick testing. Also for its debugging features.
 - [Ghidra](https://github.com/NationalSecurityAgency/ghidra) in combination with the [PSX Executable Loader Plugin](https://github.com/lab313ru/ghidra_psx_ldr) for reverse engineering functions in the game.

## Special Thanks

 - Redhot
 - OddKara
 - wafflewizard1
 - Newantox

## Known Bugs

1. When re-entering a homeworld/level or dying, AFTER killing enemies and making them hold orbs instead of their gems, the redistribution can become shuffled causing an incorrect amount of total gems in a level. This only ever makes it become slightly over, or slightly under however, so isn't too detrimental. 

2. Some spring chests change color correspondent to their changed value, while some don't. I think the behavior of how spring chests color is determined was changed through the development of the game (if I had to guess)


## Contact

If you need any help building this project, or are trying to get into spyro/game modding in general, feel free to reach out to me on discord: **Composer#7458**
