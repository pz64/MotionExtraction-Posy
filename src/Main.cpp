// MotionDetection.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "MotionExtraction.h"
#include<limits>

int main()
{

    pz::MotionExtraction extraction{ "../samples/snow.mp4" };
    extraction.setFrameOffset(10000);
    extraction.render();
    return 0;
}
