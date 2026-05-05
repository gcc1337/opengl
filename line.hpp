#pragma once

#include <vector>

#include "vec.hpp"
#include "shader.hpp"
#include "shape.hpp"

class Line : public Shape
{
public:
	Line();
	Line(std::vector<vec3> points, vec3 color);
	Line(std::vector<vec3> points, std::vector<vec3> colors);
	void draw();

private:
};