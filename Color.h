#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

class Color
{
public:
	float R, G, B, A;
	//rgba = 0.0f - 1.0f
	Color(float _R, float _G, float _B, float _A);

	uint32_t ToUInt32() const;

	Color operator + (const Color &c) const;
	Color operator - (const Color &c) const;
	Color operator * (float f) const;
};

#endif // COLOR_H
