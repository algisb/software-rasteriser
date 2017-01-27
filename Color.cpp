#include <Color.h>

Color::Color(float _R, float _G, float _B, float _A)
{
	this->R = _R;
	this->G = _G;
	this->B = _B;
	this->A = _A;
}

uint32_t Color::ToUInt32() const
{
	uint8_t r = (uint8_t)(R * 255.0f);
	uint8_t g = (uint8_t)(G * 255.0f);
	uint8_t b = (uint8_t)(B * 255.0f);
	uint8_t a = (uint8_t)(A * 255.0f);

	return (a << 24) | (r << 16) | (g << 8) | b;
}

Color Color::operator + (const Color &c) const
{
	return Color(R + c.R, G + c.G, B + c.B, A + c.A);
}

Color Color::operator - (const Color &c) const
{
	return Color(R - c.R, G - c.G, B - c.B, A - c.A);
}

Color Color::operator * (float f) const
{
	return Color(R * f, G * f, B * f, A * f);
}
