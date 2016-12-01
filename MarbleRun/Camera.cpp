#include <memory>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "Camera.h"

Camera::Camera() : 
	_capture(0), 
	_bb_x(200),
	_bb_y(150),
	_bb_width(225),
	_bb_height(175) {
	_stream = std::make_unique<cv::VideoCapture>(0);
	cv::namedWindow("Camera");
}

Camera::~Camera() {
	
}

bool Camera::isConnected() {
	return _stream->isOpened();
}

void Camera::updateDisplay() {
	if (_capture % 50 == 0) {
		cv::Mat cameraFrame;
		cv::Mat overlay;
		cv::Mat output;
		double alpha = 0.2;

		_stream->read(cameraFrame);

		cameraFrame.copyTo(overlay);
		cv::rectangle(overlay, 
			cv::Rect(_bb_x, _bb_y, _bb_width, _bb_height),
			cv::Scalar(0, 0, 139), 3);

		cv::addWeighted(cameraFrame, alpha,
			overlay, 1 - alpha, 
			0, output);

		imshow("Camera", output);
	}
	_capture++;
}

void Camera::bbLeft() {
	_bb_x = std::max(_bb_x - 10, 0);
}

void Camera::bbRight() {
	_bb_x = std::min(_bb_x + 10, 640-_bb_width);
}

void Camera::bbUp() {
	_bb_y = std::max(_bb_y - 10, 0);
}

void Camera::bbDown() {
	_bb_y = std::min(_bb_y + 10, 480 - _bb_height);
}

void Camera::bbIncreaseSize() {
	_bb_width = (int)(_bb_width * 1.05);
	_bb_height = (int)(_bb_height * 1.05);
}

void Camera::bbDecreaseSize() {
	_bb_width = (int)(_bb_width * 0.95);
	_bb_height = (int)(_bb_height * 0.95);
}