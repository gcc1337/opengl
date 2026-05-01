#include "shape.hpp"
#include <iostream>

Shape::Shape(std::vector<vec3> vertices, vec3 color)
	:vertices_{vertices}
{
	//ineficient implementation to create vertices and colors intercalation
	//operations and memory, this fuction uses a aux vector with length of vertices.size * colors
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

	//configure first vao atribute, position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//configure second vao atribute, color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Shape::draw()
{
	glBindVertexArray(vaoID_);
	//vertices has to form a "zig-zag" pattern
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices_.size());
}

void Shape::changeVertex(int vertex_index, vec3 new_value, vec3 new_color)
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID_);

	if (vertex_index <= vertices_.size() - 1) {
		//this change vertex position
		glBufferSubData(GL_ARRAY_BUFFER, vertex_index * 6 * sizeof(float), 3 * sizeof(float), &new_value);
		//this change vertex color
		glBufferSubData(GL_ARRAY_BUFFER, (vertex_index * 6 * sizeof(float)) + 3 * sizeof(float), 3 * sizeof(float), &new_color);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}