#pragma once

#include <glad/glad.h>
#include <vector>

struct vec3
{
	float x{};
	float y{};
	float z{};
};

class Shape
{
public:
	Shape(std::vector<vec3> vertices, vec3 shapeColor);
	void draw();
private:
	unsigned int vaoID_{};
	unsigned int vboID_{};
	std::vector<vec3> vertices_{};
};