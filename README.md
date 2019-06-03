# YOLO GPU C++ Wrapper Library
This code is a c++ wrapper for the GPU version of YOLO DNN source code. It's main purpose is provide the ability of using YOLO DNN inside any C++ code. This repo was originally developed by [Eslam Ahmed](https://www.linkedin.com/in/eslam-ahmed-a54566b2) as a fork of the original [Darknet repo](https://github.com/pjreddie/darknet) and then restructured and change to build with CMake in this repo.
## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. **Please be noted that this code is tested on Ubuntu OS only**
### Prerequisites
Things you need on your local machine, in order to be able to compile the library:
- Nvidia GPU with minimum **2 GB** GPU RAM.
- Nvidia Driver
```
$ sudo apt-get update
$ sudo apt-get upgrade
$ sudo add-apt-repository ppa:graphics-drivers
$ sudo apt-get update
$ sudo apt-get install nvidia-370
```
- Cuda Library
```
$ cd ~/Downloads
$ wget https://developer.download.nvidia.com/compute/cuda/8.0/secure/Prod2/local_installers/cuda_8.0.61_375.26_linux.run
$ sudo bash cuda_8.0.61_375.26_linux-run --silent --toolkit
$ echo "export PATH=/usr/local/cuda-8.0/bin${PATH:+:${PATH}}" >> ~/.bashrc
$ echo "export LD_LIBRARY_PATH=/usr/local/cuda-8.0/lib64 ${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}" >> ~/.bashrc
$ source ~/.bashrc
```
- OpenCV Library
```
$ sudo apt-get install build-essential
$ sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
$ sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
$ cd ~/Downloads
$ wget https://github.com/opencv/opencv/archive/2.4.13.5.zip
$ unzip -u 2.4.13.5.zip
$ cd opencv-2.4.13.5
$ mkdir build
$ cd build
$ cmake -DWITH_OPENCL=OFF -DBUILD_EXAMPLES=OFF -DWITH_CUDA=OFF ..
$ make -j
$ sudo make install
```
### Installation
To compile the library and install it to your **/usr/local/lib/**, please follow these steps:
```
$ git clone https://github.com/ahmedfawzyelaraby/yolo-v2-gpu-wrapper.git
$ cd [to_the_code_directory]/yolo-v2-gpu-wrapper
$ mkdir build
$ cd build
$ cmake ..
$ make -j
$ sudo make install
```
### Deployment
To use this library in your c++ code, you have to add some c++ lines of code and edit your cmake to include:
#### C++ Code Example
Main.cpp
```
#include "opencv2/opencv.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include "yolo.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Yolo yolo;
	yolo.setConfigFilePath("[path_to_cfg_file]");
	yolo.setDataFilePath("[path_to_data_file]");
	yolo.setWeightFilePath("[path_to_weights_file]");
	yolo.setAlphabetPath("[path_of_directory_of_labels]");
	yolo.setNameListFile("[path_to_names_file]");
	cv::VideoCapture capture("[path_to_test_video]");
	cv::Mat img;
	while(true)
	{
		capture >> img;
		std::vector<DetectedObject> detection;
		yolo.detect(img, detection);

		for(int i = 0; i < detection.size(); i++)
		{
			DetectedObject& o = detection[i];
			cv::rectangle(img, o.bounding_box, cv::Scalar(255,0,0), 2);

			const char* class_name = yolo.getNames()[o.object_class];

			char str[255];
			sprintf(str,"%s", class_name);

			cv::putText(img, str, cv::Point2f(o.bounding_box.x,o.bounding_box.y), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0,0,255), 2);
			cv::imshow("video", img);
		}
		cv::waitKey(1);
	}
	return 0;
}
```
#### CMake Example
CMakeLists.txt
```
CMAKE_MINIMUM_REQUIRED  (VERSION 2.8.3)
PROJECT([project_name_you_choose])

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FIND_PACKAGE(CUDA REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)

INCLUDE_DIRECTORIES(/usr/local/include/yolo-v2-gpu-wrapper)
INCLUDE_DIRECTORIES(${CUDA_INCLUDE_DIRS})

ADD_EXECUTABLE(${PROJECT_NAME} Main.cpp)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS} libYOLOGPUWrapper.so)

```
