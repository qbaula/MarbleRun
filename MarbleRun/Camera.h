#pragma once
#include <vector>
#include <memory>
#include <opencv2\highgui\highgui.hpp>

/*
namespace cv {
    class VideoCapture;
	class Mat;
} 
*/

class Color;
struct b2Vec2;

class Camera {
public:
	std::vector<std::vector<cv::Point>> _contours;
	std::vector<Color> _colors;

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
	int getBBWidth();
	int getBBHeight();

	void getContours();
	Color getContourColor(int x, int y);

private:
	std::unique_ptr<cv::VideoCapture> _stream;
	cv::Mat* _bounded;

	int _capture;
	int _bb_x;
	int _bb_y;
	int _bb_width;
	int _bb_height;

	void bbCapture();
};