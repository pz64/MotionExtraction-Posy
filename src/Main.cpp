// MotionDetection.cpp : Defines the entry point for the application.
//

#include<limits>
#include <print>
#include "MotionExtraction.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

int main()
{
	auto windowName{ "Motion Extraction" };

	cv::namedWindow(windowName, cv::WINDOW_KEEPRATIO);

	pz::MotionExtraction extraction{ "../samples/walk2.mp4" };

	extraction.frameOffset = 1000;

	for (double f = 0; f < extraction.totalFrames; ++f)
	{
		auto mat = extraction.getDiff(f);

		if (mat.has_value())
		{
			cv::imshow(windowName, mat.value());
		}
		else if (mat.error() == pz::Error::MAT_EMPTY)
		{
			std::println(stderr,"Error: MAT_EMPTY");
			break;
		}
		else if (mat.error() == pz::Error::READ_ERROR)
		{
			std::println(stderr, "Error: READ_ERROR");
			break;
		}

		// Press  ESC on keyboard to exit
		char c = (char)cv::waitKey(25);
		if (c == 27)
			break;
	}

	return 0;
}

