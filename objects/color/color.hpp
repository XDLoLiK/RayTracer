#pragma once

using color_t = unsigned char;

class Color {
private:
    color_t red_   = 255;
    color_t green_ = 0;
    color_t blue_  = 0;
    color_t alpha_ = 255;

public:
    Color(color_t red_,  color_t green_, 
          color_t blue_, color_t alpha_);
    Color &operator+=(const Color &color);
    ~Color();

    color_t red()   const;
    color_t green() const;
    color_t blue()  const;
    color_t alpha() const;
};

Color operator*(const Color &color, long double num);
Color operator+(const Color &color1, const Color &color2);

const Color black = Color(0,   0,   0,   255);
const Color white = Color(255, 255, 255, 255);
const Color red   = Color(255, 0,   0,   255);
const Color green = Color(0,   255, 0,   255);
const Color blue  = Color(0,   0,   255, 255);
const Color grey  = Color(64,  64,  64,  255);
