#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <vector>
#include <iostream>
#include <Color.h>
#include <math.h>
#include <glm.hpp> // This is the main GLM header
#include <matrix_transform.hpp>
//The attributes of the screen
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int SCREEN_BPP = 32;

class Span;
class Rasterizer
{
protected:
	uint32_t *m_FrameBuffer;
	unsigned int m_Width, m_Height;
public:
	void SetFrameBuffer(uint32_t * _frameBuffer, unsigned int _width, unsigned int _height);
	void SetPixel(glm::ivec2 _pos, Color * _color);
	void DrawLine(Color * _color0, glm::ivec2 _pos0, Color * _color1, glm::ivec2 _pos1);
	void DrawWireTriangle(Color * _color0, glm::ivec2 _pos0, Color * _color1, glm::ivec2 _pos1, Color * _color2, glm::ivec2 _pos2);
	void DrawTriangle(Color * _color0, glm::ivec2 _pos0, Color * _color1, glm::ivec2 _pos1, Color * _color2, glm::ivec2 _pos2);
	float AreaOfTriangle(float _a, float _b, float _c);
	void DrawTriangle1(Color * _color0, glm::ivec2 _pos0, Color * _color1, glm::ivec2 _pos1, Color * _color2, glm::ivec2 _pos2);
	bool pointInTriangle2D(glm::ivec2 _point, glm::ivec2 _pos0, glm::ivec2 _pos1, glm::ivec2 _pos2);
	int DrawTriangles(std::vector<glm::vec3> * _vertexData, glm::mat4 _MVP);
};

#endif //RASTERIZER_H
