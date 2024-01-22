# ToyStory2Fix++

ToyStory2Fix++ aims to provide a complete All-In-One enhancement package for the AbandonWare game, "Toy Story 2: Buzz Lightyear to the Rescue"

Some key points,
* Includes everything [this](https://github.com/RibShark/ToyStory2Fix/tree/master) mentions but more. Uses the same asi script fix to enable higher res, 60 fps, etc.
* Includes all movies and audio files.
* Patched the DRM check, registry checks and have written a subroutine to write the right directory paths to the proper addresses.
* Rewrote Game Code to read Data from the Current Active Directory instead of the CD, so you don't have to insert a CD or virtually mount it everytime you want to play the game.
* Wrote a little trainer in cpp/asm (ManiacTrainer.dll and patches inside game code) which includes some general player stuff and a level unlocker (Edit tokens for each level)
* Use Config.ini to change the trainer constants, can be refreshed mid-game by the set key (Trainer is disabled by default).
* You can use DXWND and the config files I've included to play the game in windowed mode.

# Download
[MEGA Link](https://mega.nz/file/aKJTWYhJ#V8AD8-EzsSY0V0vI79jEliAWnhJmoYAfyhkVlKHa_uA)

Extract the archive and launch Toy2.exe to play the game.

Optionally Setup DXWND to play the game in windowed mode.

**Note: Above is the source code for the DLL Trainer only. Everything else has been directly patched into the executable file.**
