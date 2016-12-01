#pragma once
#include <memory>

namespace cv {
    class VideoCapture;
}

class Camera {
public:
	Camera();
	~Camera();

	bool isConnected();
	void updateDisplay();

private:
	std::unique_ptr<cv::VideoCapture> _stream;
	int _capture;
};