#include<algorithm>
#include <expected>
#include "MotionExtraction.h"

pz::MotionExtraction::MotionExtraction(std::string videoPath)
{
	_videoCapture = cv::VideoCapture(videoPath);

	if (!_videoCapture.isOpened())
	{
		std::cout << "Error opening video stream or file" << std::endl;
	}

	totalFrames = _videoCapture.get(cv::CAP_PROP_FRAME_COUNT);
}

pz::MotionExtraction::~MotionExtraction()
{
	_videoCapture.release();
	cv::destroyAllWindows();
}

auto pz::MotionExtraction::getDiff(double currentOffset) -> std::expected<cv::Mat, pz::Error>
{
	auto targetFrame = std::clamp(currentOffset - frameOffset, 0.0, currentOffset);

	_videoCapture.set(cv::CAP_PROP_POS_FRAMES, targetFrame);

	if (!_videoCapture.read(_overlayFrame))
	{
		return std::unexpected(Error::READ_ERROR);
	}

	_videoCapture.set(cv::CAP_PROP_POS_FRAMES, currentOffset);

	if (!_videoCapture.read(_frame))
	{
		return std::unexpected(Error::READ_ERROR);
	}

	if (_frame.empty() || _overlayFrame.empty())
	{
		return std::unexpected(Error::MAT_EMPTY);
	}
	

	cv::absdiff(_frame, _overlayFrame, _diffFrame);
	
	return _diffFrame;
}
