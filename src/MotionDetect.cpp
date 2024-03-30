#include<algorithm>
#include "MotionDetect.h"
#include "opencv2/opencv.hpp"

pz::MotionDetect::MotionDetect(std::string videoPath)
{
	_videoCapture = std::make_unique<cv::VideoCapture>(videoPath);

	if (!_videoCapture->isOpened())
	{
		std::cout << "Error opening video stream or file" << std::endl;
	}
}

pz::MotionDetect::~MotionDetect()
{
	_videoCapture->release();
	cv::destroyAllWindows();
}

void pz::MotionDetect::setFrameOffset(std::size_t offset)
{
	_frameOffset = offset;
}

void pz::MotionDetect::render()
{
	cv::Mat frame, overlayFrame, diffFrame;

	while (true)
	{

		auto currentFrame = _videoCapture->get(cv::CAP_PROP_POS_FRAMES);

		std::size_t targetFrame = std::clamp(static_cast<double>( currentFrame - _frameOffset), 0.0, currentFrame);

		_videoCapture->set(cv::CAP_PROP_POS_FRAMES, targetFrame);
		_videoCapture->read(overlayFrame);

		_videoCapture->set(cv::CAP_PROP_POS_FRAMES, currentFrame);
		_videoCapture->read(frame);

		if (frame.empty() || overlayFrame.empty())
			break;

	
		cv::absdiff(frame, overlayFrame, diffFrame);

		cv::imshow("Frame", diffFrame);

		// Press  ESC on keyboard to exit
		char c = (char)cv::waitKey(25);
		if (c == 27)
			break;
	}
}
