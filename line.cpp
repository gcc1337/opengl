#include "line.hpp"
#include "shape.hpp"

Line::Line()
	:Shape{}
{
}

Line::Line(std::vector<vec3> points, vec3 color)
	:Shape{ points, color }
{
}

Line::Line(std::vector<vec3> points, std::vector<vec3> colors)
	:Shape{points,colors}
{
}

void Line::draw()
{
	shader_.use();
	glBindVertexArray(vaoID_);
	//vertices has to form a "zig-zag" pattern
	glDrawArrays(GL_LINE_STRIP, 0, vertices_.size());
}