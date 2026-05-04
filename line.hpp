#pragma once

#include <vector>

#include "vec.hpp"
#include "shader.hpp"
#include "shape.hpp"

class Line : Shape
{
public:
	Line(std::vector<vec3> points, vec3 color);
	void draw();

private:
};