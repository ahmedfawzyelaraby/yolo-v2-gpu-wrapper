#YOLO Standalone Wrapper Library
This code is a c++ wrapper for YOLO DNN. It's main purpose is provide the ability of using YOLO DNN inside any C++ code.
##Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. **Please be noted that this code is compatible with Ubuntu OS only**
###Prerequisites
Things you need on your local machine, in order to be able to compile the library.
```
- Nvidia GPU
- Compatible Nvidia Driver
- Cuda Library
- OpenCV Library
```
###Installation
To compile the library and install it to your **/usr/local/lib/**, please follow these steps:
```
$ git clone https://AhmedFawzyElaraby@bitbucket.org/AhmedFawzyElaraby/yolo_standalone_wrapper.git
$ cd [to_the_code_directory]/yolo_standalone_wrapper
$ mkdir build
$ cd build
$ cmake ..
$ make -j
$ make -j
$ sudo make install
```
###Deployment