#pragma once

#include <glad/glad.h>
#include <vector>

#include "shader.hpp"
#include "shape.hpp"
#include "vec.hpp"

class Shape
{
public:
	Shape(std::vector<vec3> vertices, vec3 shapeColor);
	Shape(vec3 circ_pos, float radius, vec3 shapeColor);
	virtual ~Shape();

	void draw();
	void changeVertex(int vertex_index, vec3 new_value, vec3 new_color);
	void changeRadius(float radius);
	void changePos(vec3 pos);
	void changePosTriangle(vec3 pos);
	void changeColor(vec3 pos);
	std::vector<vec3> getVertices();
	
	//this method only change the 3 first vertices, isosceles triangle properties
	void changeSize(float new_width, float new_height);

protected:
	unsigned int vaoID_{};
	unsigned int vboID_{};
	std::vector<vec3> vertices_{};
	vec3 color_{};
	Shader shader_;
	vec3 posMod{};

};