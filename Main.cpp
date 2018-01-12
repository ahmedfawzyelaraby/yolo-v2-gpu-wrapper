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



int main()
{

//    int nDevices = 1;

//    cudaGetDeviceCount(&nDevices);
//    for (int i = 0; i < nDevices; i++) {
//      cudaDeviceProp prop;
//      cudaGetDeviceProperties(&prop, i);
//      printf("Device Number: %d\n", i);
//      printf("  Device name: %s\n", prop.name);
//      printf("  Memory Clock Rate (KHz): %d\n",
//             prop.memoryClockRate);
//      printf("  Memory Bus Width (bits): %d\n",
//             prop.memoryBusWidth);
//      printf("  Peak Memory Bandwidth (GB/s): %f\n\n",
//             2.0*prop.memoryClockRate*(prop.memoryBusWidth/8)/1.0e6);
//      std::cout << "pciDeviceID" << prop.pciDomainID << std::endl;
//    }
////     std::ofstream file("out.csv");
//     int frame_no = 0;
//     char delimiter = ',';

     Yolo yolo;
//     yolo.setConfigFilePath("/home/ahmedfawzyelaraby/Thesis_WS/Code/YOLO_Darknet/darknet_old/cfg/yolo.cfg");
//     yolo.setDataFilePath("/home/ahmedfawzyelaraby/Thesis_WS/Code/YOLO_Darknet/darknet_old/cfg/coco.data");
//     yolo.setWeightFilePath("/home/ahmedfawzyelaraby/Thesis_WS/Code/YOLO_Darknet/darknet_old/yolo.weights");
//     yolo.setAlphabetPath("/home/ahmedfawzyelaraby/Thesis_WS/Code/YOLO_Darknet/darknet_old/data/labels/");
//     yolo.setNameListFile("/home/ahmedfawzyelaraby/Thesis_WS/Code/YOLO_Darknet/darknet/data/coco.names");
     yolo.setConfigFilePath("/home/ahmedfawzyelaraby/Thesis_WS/Code/YOLO_Darknet/darknet_old/cfg/tiny-yolo-voc.cfg");
     yolo.setDataFilePath("/home/ahmedfawzyelaraby/Thesis_WS/Code/YOLO_Darknet/darknet_old/cfg/voc.data");
     yolo.setWeightFilePath("/home/ahmedfawzyelaraby/Thesis_WS/Code/YOLO_Darknet/darknet_old/tiny-yolo-voc.weights");
     yolo.setAlphabetPath("/home/ahmedfawzyelaraby/Thesis_WS/Code/YOLO_Darknet/darknet_old/data/labels/");
     yolo.setNameListFile("/home/ahmedfawzyelaraby/Thesis_WS/Code/YOLO_Darknet/darknet/data/voc.names");


//     yolo.setConfigFilePath("/home/avidbeam-devsrvr-1/Desktop/michael/darknet/cfg/yolov1/yolo-small.cfg");
//     yolo.setDataFilePath("/home/avidbeam-devsrvr-1/Desktop/michael/yolo_cpp/cfg/coco.data");
//     yolo.setWeightFilePath("/home/avidbeam-devsrvr-1/Desktop/michael/darknet/cfg/yolo-small.weights");
//     yolo.setAlphabetPath("/home/avidbeam-devsrvr-1/Desktop/michael/yolo_cpp/data/labels/");
//     yolo.setNameListFile("/home/avidbeam-devsrvr-1/Desktop/michael/yolo_cpp/data/coco.names");

     cv::VideoCapture capture("/home/ahmedfawzyelaraby/Downloads/Lincoln (2012) [1080p]/Lincoln.2012.1080p.Bluray.x264.YIFY.mp4");
     if(!capture.isOpened())
     {
         std::cout << "cannot read video file" << std::endl;
         return 0;
     }
     const clock_t begin_time = clock();

     cv::Mat img;
     while(true)
     {
         capture >> img;
//         img=imread("/home/avidbeam-devsrvr-1/DinaWorkspace/mxnet-ssd.cpp/demo/street.jpg");
         //resize(img, img, Size(img.cols/2, img.rows/2));
    //     if(img.empty())
      //       break;

         //cv::resize(img, img, cv::Size(544,544));

         std::vector<DetectedObject> detection;
         std::cout << img.cols << "  rows: " << img.rows << std::endl;
         yolo.detect(img, detection);
         cout << detection.size() << endl;
         for(int i = 0; i < detection.size(); i++)
         {
             DetectedObject& o = detection[i];
             cv::rectangle(img, o.bounding_box, cv::Scalar(255,0,0), 2);

             const char* class_name = yolo.getNames()[o.object_class];

             char str[255];
             //sprintf(str,"%s %f", names[o.object_class], o.prob);
             sprintf(str,"%s", class_name);
             cv::putText(img, str, cv::Point2f(o.bounding_box.x,o.bounding_box.y), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0,0,255), 2);

//             if( strcmp(class_name,"person") == 0)
//             {
//                 std::ostringstream oss;
//                 oss << frame_no << delimiter
//                     << o.bounding_box.x << delimiter
//                     << o.bounding_box.y << delimiter
//                     << o.bounding_box.width << delimiter
//                     << o.bounding_box.height;
////                 file << oss.str().c_str() << std::endl;
//             }
         }

         cv::imshow("video", img);
//         cv::imwrite("/home/avidbeam-devsrvr-1/Ghada/Segmentation/Results/YOLO-CPP/street.jpg",img);
         std::cout <<"Time ........" <<float( clock () - begin_time ) /  CLOCKS_PER_SEC;

         cv::waitKey(1);

//         frame_no++;
     }

    return 0;
}
