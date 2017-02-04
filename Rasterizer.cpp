#include <Rasterizer.h>


void Rasterizer::SetFrameBuffer(uint32_t *_frameBuffer, unsigned int _width, unsigned int _height)
{
	m_FrameBuffer = _frameBuffer;
	m_Width = _width;
	m_Height = _height;
}

void Rasterizer::SetPixel(glm::ivec2 _pos, Color * _color)
{
	if (_pos.x >= m_Width || _pos.y >= m_Height)
	{
		return;
	}

	m_FrameBuffer[_pos.y * m_Width + _pos.x] = _color->ToUInt32();
}

void Rasterizer::DrawLine(Color * _color0, glm::ivec2 _pos0, Color * _color1, glm::ivec2 _pos1)
{
	glm::vec2 v = _pos1 - _pos0;
	glm::vec2 vn = glm::normalize(v);
	float vm = glm::length(v);



	for (float i = 1; i < vm+1; i++)
	{
		float rt1 = i / vm;
		float rt0 = 1 - rt1;
		Color c = (*_color0 * rt0) + (*_color1 * rt1);
		glm::vec2 vi = vn * i;
		SetPixel(_pos0 + (glm::ivec2)vi, &c);


	}


}

void Rasterizer::DrawWireTriangle(Color * _color0, glm::ivec2 _pos0, Color * _color1, glm::ivec2 _pos1, Color * _color2, glm::ivec2 _pos2)
{
	DrawLine(_color0, _pos0, _color1, _pos1);
	DrawLine(_color0, _pos0, _color2, _pos2);
	DrawLine(_color1, _pos1, _color2, _pos2);
}

float Rasterizer::AreaOfTriangle(float _a, float _b, float _c)
{
	float s = (_a + _b + _c) / 2;
	float a = sqrt(s*((s-_a)*(s-_b)*(s-_c)));
	return a;
}

bool Rasterizer::pointInTriangle2D(glm::ivec2 _point, glm::ivec2 _pos0, glm::ivec2 _pos1, glm::ivec2 _pos2)
{

	glm::vec2 v0;
	v0 = (glm::vec2)(_pos1 - _pos0);
	float vm0 = glm::length(v0);

	glm::vec2 v1;
	v1 = (glm::vec2)(_pos2 - _pos0);
	float vm1 = glm::length(v1);

	glm::vec2 v2;
	v2 = (glm::vec2)(_pos2 - _pos1);
	float vm2 = glm::length(v2);


	glm::vec2 vp0;
	vp0 = (glm::vec2)(_pos0 - _point);
	float vpm0 = glm::length(vp0);

	glm::vec2 vp1;
	vp1 = (glm::vec2)(_pos1 - _point);
	float vpm1 = glm::length(vp1);

	glm::vec2 vp2;
	vp2 = (glm::vec2)(_pos2 - _point);
	float vpm2 = glm::length(vp2);

	float tA = AreaOfTriangle(vm0,vm1,vm2);

	float u = AreaOfTriangle(vm0, vpm0, vpm1) ;
	float v = AreaOfTriangle(vm1, vpm0, vpm2) ;
	float w = AreaOfTriangle(vm2, vpm1, vpm2) ;

	//float gt = 0.0f;
	//float lt = 1.0f;
	//if ((u > gt) && (v > gt) && (w > gt) && (u < lt) && (v < lt) && (w < lt))
	//{
		if (((u + v + w)<= tA+2) &&  ((u + v + w) >= 0.0f))
		{
			return true;
		}
	//}

	else
	{
		return false;
	}


	////float u = glm::dot(vn0, v2);
	////float v = glm::dot(vn1, v2);

	//// Compute dot products
	//float dot00 = glm::dot(v0, v0);

	//float dot01 = glm::dot(v0, v1);

	//float dot02 = glm::dot(v0, v2);

	//float dot11 = glm::dot(v1, v1);

	//float dot12 = glm::dot(v1, v2);

	//// Compute barycentric coordinates
	//float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	//float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	//float v = (dot00 * dot12 - dot01 * dot02) * invDenom;


	//// Check if point is in triangle

	//if ((u >= 0) && (v >= 0) && (u <= 1) && (v <= 1) && (u + v <= 1))
	//{
	//	return true;
	//}

	//else
	//{
	//	return false;
	//}
}

void Rasterizer::DrawTriangle(Color * _color0, glm::ivec2 _pos0, Color * _color1, glm::ivec2 _pos1, Color * _color2, glm::ivec2 _pos2)
{
	//DrawLine(_color0, _pos0, _color1, _pos1);
	//DrawLine(_color0, _pos0, _color2, _pos2);

	glm::vec2 v0 = _pos1 - _pos0;
	glm::vec2 vn0 = glm::normalize(v0);
	float vm0 = glm::length(v0);

	glm::vec2 v1 = _pos2 - _pos0;
	glm::vec2 vn1 = glm::normalize(v1);
	float vm1 = glm::length(v1);

	float gm;
	if (vm0>vm1)
	{
		gm = vm0;
	}
	else
	{
		gm = vm1;
	}

	for (float i = 1; i < gm; i++)
	{
		float rt10 = i / vm0;
		float rt00 = 1 - rt10;

		Color c0 = (*_color0 * rt00) + (*_color1 * rt10);
		glm::vec2 vi0 = vn0 * i;
		if (i>vm0)
		{
			vi0 = vn0*vm0;
		}
		glm::ivec2 fPos0 = _pos0 + (glm::ivec2)vi0;



		float rt11 = i / vm1;
		float rt01 = 1 - rt11;

		Color c1 = (*_color0 * rt01) + (*_color2 * rt11);
		glm::vec2 vi1 = vn1 * i;
		if (i>vm1)
		{
			vi1 = vn1*vm1;
		}

		glm::ivec2 fPos1 = _pos0 + (glm::ivec2)vi1;

		DrawLine(&c0, fPos0, &c1, fPos1);
	}

}

void Rasterizer::DrawTriangle1(Color * _color0, glm::ivec2 _pos0, Color * _color1, glm::ivec2 _pos1, Color * _color2, glm::ivec2 _pos2)
{

	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			if (pointInTriangle2D(glm::ivec2(x,y),_pos0,_pos1,_pos2))
			{
				glm::vec2 v0;
				v0 = (glm::vec2)(_pos1 - _pos0);
				float vm0 = glm::length(v0);

				glm::vec2 v1;
				v1 = (glm::vec2)(_pos2 - _pos0);
				float vm1 = glm::length(v1);

				glm::vec2 v2;
				v2 = (glm::vec2)(_pos2 - _pos1);
				float vm2 = glm::length(v2);


				glm::vec2 vp0;
				vp0 = (glm::vec2)(_pos0 - glm::ivec2(x, y));
				float vpm0 = glm::length(vp0);

				glm::vec2 vp1;
				vp1 = (glm::vec2)(_pos1 - glm::ivec2(x, y));
				float vpm1 = glm::length(vp1);

				glm::vec2 vp2;
				vp2 = (glm::vec2)(_pos2 - glm::ivec2(x, y));
				float vpm2 = glm::length(vp2);

				float tA = AreaOfTriangle(vm0, vm1, vm2);

				float u = AreaOfTriangle(vm0, vpm0, vpm1)/tA;
				float v = AreaOfTriangle(vm1, vpm0, vpm2)/tA;
				float w = AreaOfTriangle(vm2, vpm1, vpm2)/tA;

				Color tmpCol0 = *_color0 * glm::abs(w);
				Color tmpCol1 = *_color1 * glm::abs(v);
				Color tmpCol2 = *_color2 * glm::abs(u);
				Color tmpCol = tmpCol0 + tmpCol1 + tmpCol2;

				SetPixel(glm::ivec2(x, y), &tmpCol);
			}

		}
	}

}

int Rasterizer::DrawTriangles(std::vector<glm::vec3> * _vertexData, glm::mat4 _MVP)
{
    Color color0(1.0f, 0.0f, 0.0f, 1.0f);
    Color color1(0.0f, 1.0f, 0.0f, 1.0f);
    Color color2(0.0f, 0.0f, 1.0f, 1.0f);
//
    for(int i = 0; i < _vertexData->size(); i=i+3)
    {
        //glm::vec3 k = (*_vertexData)[i];
        glm::vec4 v0 = _MVP * glm::vec4((*_vertexData)[i+0].x, (*_vertexData)[i+0].y, (*_vertexData)[i+0].z, 1.0f);
        glm::vec4 v1 = _MVP * glm::vec4((*_vertexData)[i+1].x, (*_vertexData)[i+1].y, (*_vertexData)[i+1].z, 1.0f);
        glm::vec4 v2 = _MVP * glm::vec4((*_vertexData)[i+2].x, (*_vertexData)[i+2].y, (*_vertexData)[i+2].z, 1.0f);

        glm::vec2 p0((v0.x / v0.w)*SCREEN_WIDTH/2  + SCREEN_WIDTH / 2, (v0.y / v0.w)*SCREEN_HEIGHT/2 + SCREEN_HEIGHT / 2);
        glm::vec2 p1((v1.x / v1.w)*SCREEN_WIDTH/2  + SCREEN_WIDTH / 2, (v1.y / v1.w)*SCREEN_HEIGHT/2 + SCREEN_HEIGHT / 2);
        glm::vec2 p2((v2.x / v2.w)*SCREEN_WIDTH/2  + SCREEN_WIDTH / 2, (v2.y / v2.w)*SCREEN_HEIGHT/2 + SCREEN_HEIGHT / 2);

        //glm::vec2 p0(v0.x / v0.w + SCREEN_WIDTH / 2, v0.y / v0.w + SCREEN_HEIGHT / 2);
        //glm::vec2 p1(v1.x / v1.w + SCREEN_WIDTH / 2, v1.y / v1.w + SCREEN_HEIGHT / 2);
        //glm::vec2 p2(v2.x / v2.w + SCREEN_WIDTH / 2, v2.y / v2.w + SCREEN_HEIGHT / 2);
        //DrawTriangle1(&color0, p0, &color1, p1, &color2, p2);
        //printf("\n  %f, %f \n", p0.x, p0.y);
        //printf("    %f, %f \n", p1.x, p1.y);
        //printf("    %f, %f \n", p2.x, p2.y);
        //DrawTriangle1(&color0, p0, &color1, p1, &color2, p2);
        DrawWireTriangle(&color0, p0, &color1, p1, &color2, p2);
    }

    return 0;
}
