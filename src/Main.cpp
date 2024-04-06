// MotionDetection.cpp : Defines the entry point for the application.
//

#include<limits>
#include <print>
#include "MotionExtraction.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

pz::MotionExtraction extraction{ "../samples/snow.mp4" };

int seekbar = 0;
int offsetSeekbar = 0;
auto windowName{ "Motion Extraction" };
auto seekbarName{ "Seekbar" };
auto offsetName{ "Offset" };
static auto on_seekbarChange(int progress, void* type) -> void
{
	seekbar = progress;
}

static auto on_offsetChange(int progress, void* type) -> void
{
	offsetSeekbar = progress;
}

void myButtonName_callback(int state, void* userData) {
	// do something
	printf("Button pressed\r\n");
}

int main()
{

	cv::namedWindow(windowName, cv::WINDOW_KEEPRATIO);

	cv::createTrackbar(seekbarName, windowName, &seekbar, extraction.totalFrames, on_seekbarChange);

	cv::createTrackbar(offsetName, windowName, &offsetSeekbar, extraction.totalFrames, on_offsetChange);

	while (true) {

		cv::setTrackbarPos(seekbarName, windowName, seekbar);

		extraction.frameOffset = offsetSeekbar;

		auto mat = extraction.getDiff(seekbar);

		if (mat.has_value())
		{
			cv::imshow(windowName, mat.value());
		}
		else if (mat.error() == pz::Error::MAT_EMPTY)
		{
			std::println(stderr, "Error: MAT_EMPTY");

		}
		else if (mat.error() == pz::Error::READ_ERROR)
		{
			std::println(stderr, "Error: READ_ERROR");

		}

		if (seekbar >= extraction.totalFrames)
		{
			seekbar = 0;
		}
		else
		{
			++seekbar;
		}

		// Press  ESC on keyboard to exit
		char c = (char)cv::waitKey(25);
		if (c == 27)
			break;
	}


	return 0;
}
