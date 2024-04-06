// MotionDetection.cpp : Defines the entry point for the application.
//

#include<limits>
#include <print>
#include "MotionExtraction.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

pz::MotionExtraction extraction{ "../samples/beach.mp4" };

int seekbar{};
int offsetSeekbar{};
int additive{};

bool play{ false };

auto windowName{ "Motion Extraction" };
auto seekbarName{ "Seekbar" };
auto offsetName{ "Offset" };
auto additiveName{ "Additive" };

static auto on_seekbarChange(int progress, void* type) -> void
{
	seekbar = progress;
}

static auto on_offsetChange(int progress, void* type) -> void
{
	offsetSeekbar = progress;
}

static auto on_additiveChange(int progress, void* type) -> void
{
	extraction.additive = static_cast<bool>(progress);
}

int main()
{
	cv::namedWindow(windowName, cv::WINDOW_KEEPRATIO);

	cv::createTrackbar(seekbarName, windowName, &seekbar, extraction.totalFrames, on_seekbarChange);

	cv::createTrackbar(offsetName, windowName, &offsetSeekbar, extraction.totalFrames, on_offsetChange);

	cv::createTrackbar(additiveName, windowName, &additive, 1, on_additiveChange);

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
			if (play) 
			{
				++seekbar;
			}
			
		}

		char key = static_cast<char> (cv::waitKey(25));

		switch (key)
		{
		case static_cast<int>(27):
			return 0;
		case 'c':
			extraction.clearAdditiveFrame();
			break;
		case 'p':
			play = !play;
			break;
		}
	}


	return 0;
}
