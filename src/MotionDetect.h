#pragma once
#include<string>
#include <memory>

namespace cv {
	class VideoCapture;
}

namespace pz {
	class MotionDetect {
	public:
		MotionDetect(std::string videoPath);
		~MotionDetect();

		void setFrameOffset(std::size_t offset);
		void render();


	private:
		std::unique_ptr<cv::VideoCapture> _videoCapture;
		std::size_t _frameOffset;

	};
}