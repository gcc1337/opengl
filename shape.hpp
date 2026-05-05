#pragma once

#include <glad/glad.h>
#include <vector>

#include "shader.hpp"
#include "shape.hpp"
#include "vec.hpp"

class Shape
{
public:
	Shape();
	//shape with a unique color
	Shape(std::vector<vec3> vertices, vec3 shapeColor);
	//shape with multiple colors
	Shape(std::vector<vec3> vertices, std::vector<vec3> colors);
	//create a circle shape, with a unique color
	Shape(vec3 circ_pos, float radius, vec3 shapeColor);
	virtual ~Shape();

	void draw();
	void changeVertex(int vertex_index, vec3 new_value, vec3 new_color);
	void changeRadius(float radius);
	void changePosCircle(vec3 pos);
	void changePos(vec3 pos);
	void changeColor(vec3 pos);
	std::vector<vec3> getVertices();
	virtual void addVertice(vec3 pos, vec3 color);
	virtual void removeVertice(int index);
	virtual void clear();

	
	//this method only change the first 3 vertices of a isosceles triangle properties
	void changeSize(float new_width, float new_height);

protected:
	unsigned int vaoID_{};
	unsigned int vboID_{};
	std::vector<vec3> vertices_{};
	std::vector<vec3> colors_{};
	Shader shader_{};
	vec3 posMod{};

};