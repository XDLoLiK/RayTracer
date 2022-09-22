#include "color.hpp"

Color::Color(color_t red, color_t green, 
             color_t blue, color_t alpha):
    red_(red),
    green_(green),
    blue_(blue),
    alpha_(alpha)
{

}

Color::~Color()
{
    red_   = 255;
    green_ = 255;
    blue_  = 255;
    alpha_ = 255;
}

color_t Color::red() const
{
    return red_;
}

color_t Color::green() const
{
    return green_;
}

color_t Color::blue() const
{
    return blue_;
}

color_t Color::alpha() const
{
    return alpha_;
}

Color operator*(const Color &color, long double num)
{
    unsigned newRed   = (unsigned)(color.red()   * num);
    unsigned newGreen = (unsigned)(color.green() * num);
    unsigned newBlue  = (unsigned)(color.blue()  * num);
    unsigned newAlpha = (unsigned)(color.alpha() * num);

    return Color((newRed   > 255) ? 255 : (color_t)newRed,
                 (newGreen > 255) ? 255 : (color_t)newGreen,
                 (newBlue  > 255) ? 255 : (color_t)newBlue,
                 (newAlpha > 255) ? 255 : (color_t)newAlpha);
}

Color &Color::operator+=(const Color &color)
{
    unsigned newRed   = (unsigned)color.red()   + (unsigned)red_;
    unsigned newBlue  = (unsigned)color.green() + (unsigned)green_;
    unsigned newGreen = (unsigned)color.blue()  + (unsigned)blue_;
    unsigned newAlpha = (unsigned)color.alpha() + (unsigned)alpha_;

    red_   = (newRed   > 255) ? 255 : (color_t)newRed;
    green_ = (newGreen > 255) ? 255 : (color_t)newGreen;
    blue_  = (newBlue  > 255) ? 255 : (color_t)newBlue;
    alpha_ = (newAlpha > 255) ? 255 : (color_t)newAlpha;

    return *this;
}

Color operator+(const Color &color1, const Color &color2)
{
    Color newColor = color1;
    newColor += color2;
    return newColor;
}
