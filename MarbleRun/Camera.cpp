#include <memory>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "Camera.h"

Camera::Camera() : _capture(0) {
	_stream = std::make_unique<cv::VideoCapture>(0);
}

Camera::~Camera() {
	
}

bool Camera::isConnected() {
	return _stream->isOpened();
}

void Camera::updateDisplay() {
	if (_capture % 50 == 0) {
		cv::Mat cameraFrame;
		_stream->read(cameraFrame);
		imshow("Camera", cameraFrame);
	}
	_capture++;
}