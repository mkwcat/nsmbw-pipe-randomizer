# NSMBW Pipe Randomizer

This is a mod for New Super Mario Bros. Wii that makes (almost) every pipe in the game enterable,
taking you to some other random pipe somewhere else in the game. Ghost house doors are also included
in the randomizer.

I started this mod in 2022 and it took until now (August 2024) to finally have it ready for release.
I tried to make it as polished and stable as possible, but if issues do occur there's no guarantee
I will update to fix them.

Credit to [Etrainquandt17](https://github.com/Etrainquandt17) for a lot of the manual work of assigning entrances.

## Gameplay

There are three different randomization modes, selectable in Riivolution using the "Randomize on..." choice:
- **Starting the Game** - Destinations will be consistent until the game is restarted.
- **Entering a Course** - Destinations will all be re-randomized every time a course is entered.
- **Entering a Pipe** - Entering a pipe will take you to any other pipe anywhere, with no consistency.
- **Use seed.txt** - Specify a seed for the random number generator (from 0 - 65535) with the `seed.txt` file.

Using any mode other than *Entering a Pipe* will guarantee all areas are accessible from the beginning of
at least one course, using an algorithm that prevents certain links from occurring.

Some mechanics and gameplay changes worth noting:
- Completing a course will take you to wherever that course is located on the world map.
 - Dying in any course will take you back to whichever course you entered.
- You can pause at any time to view which course you are in. If you get stuck, you are always able to exit the
course, regardless of whether you've completed it priorly or not.
- Collected Star Coins will always persist whether you complete the course or not, even if you die.
- You are no longer able to select or change the world on the world map by pressing `-`. You must play
from wherever you end up.
- Completing a course in World 9 will make it enterable from the world map, even if all the Star Coins
haven't been collected in its respective world.
- Something funny happens in multiplayer if one player reaches the flagpole and another enters a pipe.

## Installing

Download the [latest release from the releases tab](https://github.com/mkwcat/nsmbw-pipe-randomizer/releases/latest).

If using a real Wii, extract the ZIP file to the root of your SD Card or USB storage device, and
[install Riivolution](https://oscwii.org/library/app/riivolution).

If using Dolphin, extract the ZIP file to `[Dolphin User Folder]/Load/Riivolution`. You can open the
User Folder from Dolphin via `File > Open User Folder`. After that, right click on NSMBW in the game
list and click `Start with Riivolution Patches...`.

## Building

Follow these instructions if you're a developer and want to build the mod from source. You will need to use
Windows, due to CodeWarrior. If you're using another platform, you're on your own.

- First, clone this repo - `git clone https://github.com/mkwcat/nsmbw-pipe-randomizer`.
- [Clone and build Kamek](https://github.com/Treeki/Kamek). Place `Kamek.exe` and other supplimentary files
in the `Kamek` directory in this repo.
- Follow the instructions from the [Kamek README](https://github.com/Treeki/Kamek?tab=readme-ov-file#requirements)
for installing CodeWarrior. Create a `Kamek/cw` directory in this repo and place `mwcceppc.exe` and other
supplimentary files in there.
- Run `build.py` in the root of this repo. This file just runs a few commands with CodeWarrior and Kamek to build
the mod. If successful, it will have built and updated the bin files in `output/nsmbw-pipe-randomizer/Code`.

## License

The code is available under the MIT license. The full license can be found in the `LICENSE` file.

## Credits

Various credits go to many wonderful people in the New Super Mario Bros. Wii community who have made and shared tools and documentation.
Most notably [Ninji](https://github.com/Treeki), [CLF78](https://github.com/CLF78),
[RoadrunnerWMC](https://github.com/RoadrunnerWMC), [RootCubed](https://github.com/RootCubed).

And of course, credit once again to [Etrainquandt17](https://github.com/Etrainquandt17) for adding and
writing down the majority of the entrances for this mod.