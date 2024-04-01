#pragma once

#include<string>
#include<expected>
#include <memory>
#include "opencv2/opencv.hpp"

namespace pz {

	enum class Error {
		MAT_EMPTY,
		READ_ERROR,
	};

	class MotionExtraction {
	public:
		double totalFrames{};
		double frameOffset{};

		MotionExtraction(std::string videoPath);
		~MotionExtraction();

		auto getDiff(double currentOffset) -> std::expected<cv::Mat, pz::Error>;

	private:
		cv::VideoCapture _videoCapture;
		cv::Mat _frame;
		cv::Mat _overlayFrame;
		cv::Mat _diffFrame;
	};
}


