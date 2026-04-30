#include "shape.hpp"
#include <iostream>

Shape::Shape(std::vector<vec3> vertices, vec3 color)
	:vertices_{vertices}
{
	std::vector<float> data{};
	for (std::size_t i{}; i < vertices.size(); i++)
	{
		data.push_back(vertices[i].x);
		data.push_back(vertices[i].y);
		data.push_back(vertices[i].z);

		data.push_back(color.x);
		data.push_back(color.y);
		data.push_back(color.z);
	}
	
	glGenBuffers(1, &vboID_);
	glGenVertexArrays(1, &vaoID_);
	
	glBindVertexArray(vaoID_);

	glBindBuffer(GL_ARRAY_BUFFER, vboID_);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Shape::draw()
{
	glBindVertexArray(vaoID_);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices_.size());
}