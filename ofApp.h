#pragma once

#include "ofMain.h"

#include <chrono>
#include <iostream>
#include <fstream>

#include <iomanip> 
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

#ifdef _WIN32
#define OPENCV
#define GPU
#endif

#include "D:/YoloOpenFrameworks/darknet-master/include/yolo_v2_class.hpp"

#ifdef OPENCV
#include <opencv2/opencv.hpp>            // C++
#include "opencv2/core/version.hpp"
#ifndef CV_VERSION_EPOCH
#include "opencv2/videoio/videoio.hpp"
#define OPENCV_VERSION CVAUX_STR(CV_VERSION_MAJOR)"" CVAUX_STR(CV_VERSION_MINOR)"" CVAUX_STR(CV_VERSION_REVISION)
#pragma comment(lib, "opencv_world" OPENCV_VERSION ".lib")
//#include "C:\opencv\build\x64\vc14\lib\opencv_world340.dll"
#ifdef TRACK_OPTFLOW
#pragma comment(lib, "opencv_cudaoptflow" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_cudaimgproc" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_core" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_imgproc" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_highgui" OPENCV_VERSION ".lib")
#endif    // TRACK_OPTFLOW
#else
#define OPENCV_VERSION CVAUX_STR(CV_VERSION_EPOCH)""CVAUX_STR(CV_VERSION_MAJOR)""CVAUX_STR(CV_VERSION_MINOR)
#pragma comment(lib, "opencv_core" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_imgproc" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_highgui" OPENCV_VERSION ".lib")
#endif    // CV_VERSION_EPOCH

#endif

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		std::string names_file = "./bin/data/coco.names";
		std::string cfg_path = "./bin/cfg/yolov3.cfg";
		std::string weight_path = "./bin/yolov3.weights";

		std::vector<std::string> objects_from_file(std::string const filename);
		void show_console_result(std::vector<bbox_t> const result_vec, std::vector<std::string> const obj_names, int frame_id);

		std::vector<std::string> obj_names = objects_from_file(this->names_file);

		Detector detector = Detector(this->cfg_path, this->weight_path);

		cv::VideoCapture cap;
		cv::Mat cur_frame;
		std::vector<bbox_t> result_vec;

		int frame_id = 0;

};
