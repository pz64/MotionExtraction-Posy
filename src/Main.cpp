// MotionDetection.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "MotionDetect.h"
#include<limits>

int main()
{

    pz::MotionDetect detect{ "../samples/snow.mp4" };
    detect.setFrameOffset(10000);
    detect.render();
    return 0;
}
