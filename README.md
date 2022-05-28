# OSSPT10-SNAKE
CAU Open Source Software Project Team 10 term project

## Dependancies
### Global
* python 2.7
* cocos2d-x
* cmake
### Linux
* libc6:i386
* libncurses5:i386
* libstdc++6:i386
* libx11-dev
* libxmu-dev
* libglu1-mesa-dev
* libgl2ps-dev
* libxi-dev
* libzip-dev
* libpng-dev
* libcurl4-gnutls-dev
* libfontconfig1-dev
* libsqlite3-dev
* libglew-dev
* libssl-dev
* libgtk-3-dev
* binutils
* libxxf86vm-dev
### Windows
* MSVC v142
* 
## Build Instructions
This application requires [cocos2d-x](cocos.com) to run, instructions to install are as follows

### Linux
Download the latest version of cocos2d-x from [here](https://www.cocos.com/en/cocos2dx/download) and extract its contents. Once extracted, run the following
```
cd cocos2d-x-4.0
python download-deps.py
./install-deps-linux.sh
python setup.py
source ~/.bashrc
```
if using zsh run
```
source ~/.zshrc
```
instead of
```
source ~/.bashrc
```
if install-deps-linux fails dependancies must be installed manually.

if the following command outputs a version number, system is read to build
```
cocos -v
```
build and run by running
```
git clone https://github.com/eaglclaws/OSSPT10-SNAKE
cd OSSPT10-SNAKE/Snake
```
copy the contents of libchipmunk7.0.1.zip (downloadable from releases) to

OSSPT10-SNAKE/Snake/cocos2d/external/chipmunk/prebuilt/linux/64-bit and run
```
cocos run -s . -p linux -m release -o ./bin
```

### Mac
follow the steps for linux, exlcuding extracting libchipmunk and installing linux-deps, then replace
```
cocos run -s . -p linux -m release -o ./bin
```
with
```
cocos run -s . -p mac -m release -o ./bin
```

### Windows

Download the latest version of cocos2d-x from [here](https://www.cocos.com/en/cocos2dx/download) and extract its contents. Once extracted, run the following
```
cd cocos2d-x-4.0
python setup.py
```

if the following command outputs a version number, system is read to build
```
cocos -v
```

build and run by running
```
git clone https://github.com/eaglclaws/OSSPT10-SNAKE
cd OSSPT10-SNAKE/Snake
mkdir win-build
cd win-build
cmake .. -A win32
cmake --build . --config Release
cd bin\Snake\Release
.\Snake.exe
```

### Binaries
this repo also provides binary files for mac and linux, try these before building and if they do not work clone the repository and build for the respective system.
