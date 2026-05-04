#pragma once

#include <glad/glad.h>
#include <vector>

#include "shader.hpp"
#include "shape.hpp"

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
	Shape(vec3 circ_pos, float radius, vec3 shapeColor);
	void draw();
	void changeVertex(int vertex_index, vec3 new_value, vec3 new_color);
	void changeRadius(float radius);
	void changePos(vec3 pos);
	void changePosTriangle(vec3 pos);
	void changeColor(vec3 pos);
	
	//this method only change the 3 first vertices, isosceles triangle properties
	void changeSize(float new_width, float new_height);

private:
	unsigned int vaoID_{};
	unsigned int vboID_{};
	std::vector<vec3> vertices_{};
	vec3 color_{};
	Shader shader_;
};