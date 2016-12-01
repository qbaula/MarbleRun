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

	void bbLeft();
	void bbRight();
	void bbUp();
	void bbDown();

	void bbIncreaseSize();
	void bbDecreaseSize();

private:
	std::unique_ptr<cv::VideoCapture> _stream;
	int _capture;
	int _bb_x;
	int _bb_y;
	int _bb_width;
	int _bb_height;
};