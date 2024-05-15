# About
Debugging module for controlling the dynamic behavior of objects in the Unreal Engine 5 scene.
To work, the project requires the use of Unreal Engine 5, the corresponding dynamic behavior module.

Uses the file system (in and out files) to exchange data with other modules, and includes file blocking at the time of exchange.
# Using
### Config
In config.txt: 
```
InputFILE=C:\...\<out>.txt
OutputFILE=C:\...\<in>.txt
```
Specify input, output files.
### In application
In options specify input, output files.
# Build project
## Windows
### Installing pre-requisites
* Install MSYS2 and MINGW compiler - https://www.msys2.org/
### Install and build wxWidgets
* Download latest sources for windows https://www.wxwidgets.org/downloads/
* Unzip sources in some folder and open it in cmd.

Build:
* static lib:
```
cd build/msw
mingw32-make -f makefile.gcc SHARED=0 UNICODE=1 BUILD=release
```     
* shared lib
```
cd build/msw
mingw32-make -f makefile.gcc SHARED=1 UNICODE=1 BUILD=release
```    

### Build application
In project folder...
* Release
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DwxWidgets_ROOT_DIR=<Path to wxWidgets> -DwxDefault_LIB_DIR=<Path to wxWidgets>/lib/gcc_lib ..
cmake --build .
```
* Debug
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DwxWidgets_ROOT_DIR=<Path to wxWidgets> -DwxDefault_LIB_DIR=<Path to wxWidgets>/lib/gcc_lib ..
cmake --build .
```
## Linux/Unix
### Installing pre-requisites
```
sudo apt-get install build-essential
sudo apt-get install libgtk2.0-dev
sudo apt-get install libgtk-3-dev
```
### Install and build wxWidgets
* Download latest sources for linux/unix https://www.wxwidgets.org/downloads/
* Unpack and open the terminal in unpack folder
* Build library
```
cd wxWidgets-<your-version>>/
mkdir gtk-build
cd gtk-build
../configure
```
* Install library
```
sudo make install
sudo ldconfig
```
* Test installation
```
wx-config --list
wx-config --version    
```
* Clean
```
make clean
```
### Build application
In project folder...
* Release
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```
* Debug
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```