#include <memory>
#include <vector>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <Box2D\Box2D.h>
#include "Camera.h"
#include "Color.h"
#include "Logging.h"

Camera::Camera() : 
	_capture(0), 
	_bb_x(200),
	_bb_y(150),
	_bb_width(225),
	_bb_height(175),
	_bounded(nullptr) {
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


void Camera::bbCapture() {
	cv::Mat cameraFrame;
	cv::Rect bb(_bb_x, _bb_y, _bb_width, _bb_height);

	if (_bounded) {
		delete _bounded;
	}

	_stream->read(cameraFrame);
	_bounded = new cv::Mat(cameraFrame(bb));
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

int Camera::getBBWidth() {
	return _bb_width;
}

int Camera::getBBHeight() {
	return _bb_height;
}

// this function is terrible
void Camera::getContours() {
	cv::Mat bounded_gray;
	cv::Mat smooth;
	cv::Mat canny_output;
	std::vector<cv::Vec4i> hierarchy;
	
	// morph image in bounding box
	bbCapture();
	cv::cvtColor(*_bounded, bounded_gray, cv::COLOR_BGR2GRAY);
	//cv::threshold(bounded_gray, bounded_gray, 145, 255, 1);
	cv::morphologyEx(bounded_gray, smooth, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));
	//cv::GaussianBlur(bounded_gray, smooth, cv::Size(3, 3), 5, 5);
	cv::Canny(smooth, canny_output, 75, 150, 3);

	// find contours
	findContours(canny_output, _contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	// find color of contours
	_colors.clear();
	cv::Mat colored = _bounded->clone();
	for (size_t i = 0; i < _contours.size(); i++){
		cv::Rect boundingRect = cv::boundingRect(_contours[i]);
		cv::Scalar mean_color(0, 0, 0, 0);
		mean_color = cv::mean((*_bounded)(boundingRect));
		_colors.push_back(Color(mean_color));

		drawContours(colored, _contours, (int)i, mean_color, cv::FILLED);
	}


	imshow("Binary Smooth", smooth);
	imshow("Canny", canny_output);
	imshow("Colored", colored);
}

Color Camera::getContourColor(int x, int y) {
	cv::Vec3b intensity = _bounded->at<cv::Vec3b>(y, x);
	uint8_t blue = intensity.val[0];
	uint8_t green = intensity.val[1];
	uint8_t red = intensity.val[2];

	return Color(red, blue, green);
}
