![Torque Logo](http://static.garagegames.com/static/pg/logokits/Torque-Logo_H.png)
## Torque 2D 3.1 + FMOD

This branch features the FMOD audio system, completely replacing the previous OpenAL implementation.

### Build Instructions

Currently, only the OSX Xcode project files have been updated to reflect the changes made to this branch. Any help to update the other platforms would be appreaciated!

Distributing the FMOD API requires permission, so for now they have been left out of the repository here. To successfully compile this branch on OSX, follow these steps:

  1. Download the FMOD Studio Programmer's API for the Mac from here: https://www.fmod.org/download/
  2. In the location where you downloaded this branch of Torque 2D, create a fmod folder under `engine/lib`
  3. Copy all header files from the FMOD API to the `engine/lib/fmod/lowlevel/inc` folder
  4. Copy libfmod.dylib to `engine/lib/fmod/lowlevel/lib`
  5. In the Terminal, change directories to the `engine/lib/fmod/lowlevel/lib` folder and type in the following `install_name_tool -id @loader_path/libfmod.dylib libfmod.dylib`
  6. Build the project in Xcode


### Examples

The AudioToy has been updated to work with FMOD and positional audio is demonstrated in the AudioEmitterToy.


### Issues

There are a few features missing and minor bugs lurking around. More progress to come!
