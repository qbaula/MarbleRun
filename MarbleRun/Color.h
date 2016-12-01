#pragma once
enum COLOR{
	MOSTLY_RED,
	MOSTLY_GREEN,
	MOSTLY_BLUE,
	UNCLEAR
};

class Color {
public:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	Color() : r(0), g(0), b(0), a(0) {};
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {};
	Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {};
	Color(cv::Scalar s) {
		b = (uint8_t) s[0];
		g = (uint8_t) s[1];
		r = (uint8_t) s[2];
	}

	COLOR mostColor() {
		if (g + 5 >= r && g + 5 >= b) { return MOSTLY_GREEN; }
		else if (b >= r && b >= g) { return MOSTLY_BLUE; }
		else if (r >= g && r >= b) { return MOSTLY_RED; }
		else { return UNCLEAR; }
	}
};