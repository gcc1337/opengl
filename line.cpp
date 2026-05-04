#include "line.hpp"
#include "shape.hpp"

Line::Line(std::vector<vec3> points, vec3 color)
	:Shape{ points, color }
{
}

void Line::draw()
{
	shader_.use();
	glBindVertexArray(vaoID_);
	//vertices has to form a "zig-zag" pattern
	glDrawArrays(GL_LINE_STRIP, 0, vertices_.size());
}