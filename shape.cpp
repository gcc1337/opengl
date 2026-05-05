
#include "shape.hpp"
#include <iostream>

Shape::Shape() 
	:shader_{ "vertexShader.vs", "fragmentShader.fs" }
{
	glGenBuffers(1, &vboID_);
	glGenVertexArrays(1, &vaoID_);

	glBindVertexArray(vaoID_);

	glBindBuffer(GL_ARRAY_BUFFER, vboID_);
	glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);

	//configure first vao atribute, position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//configure second vao atribute, color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Shape::Shape(std::vector<vec3> vertices, vec3 color)
	:vertices_{ vertices },
	shader_{ "vertexShader.vs", "fragmentShader.fs" },
	colors_(vertices.size(), color)
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

Shape::Shape(std::vector<vec3> vertices, std::vector<vec3> colors)
	:vertices_{ vertices },
	shader_{ "vertexShader.vs", "fragmentShader.fs" },
	colors_{ colors }
{
	//ineficient implementation to create vertices and colors intercalation
	//operations and memory, this fuction uses a aux vector with length of vertices.size * colors
	std::vector<float> data{};
	for (std::size_t i{}; i < vertices.size(); i++)
	{
		data.push_back(vertices[i].x);
		data.push_back(vertices[i].y);
		data.push_back(vertices[i].z);

		data.push_back(colors[i].x);
		data.push_back(colors[i].y);
		data.push_back(colors[i].z);
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


//this constructor should be converted to its unique class, circle
//shape should be a abstract class
Shape::Shape(vec3 circ_pos, float radius, vec3 shapeColor)
	:Shape({ {-1.0f, -1.0f, 0.0f},
				  {-1.0f,  1.0f, 0.0f},
				  { 1.0f, -1.0f, 0.0f},
				  { 1.0f,  1.0f, 0.0f} }, shapeColor)
{
	//this is bad design, previous shader creation is unnecessary
	//each instance having its own shader is a bad idea, every object that is
	//draw change the shader used in the gpu, changing shader is expensive
	shader_ = Shader{ "vertexShaderCircle.vs", "fragmentShaderCircle.fs" };
	shader_.use();
	shader_.setFloat("circ_center_x", circ_pos.x);
	shader_.setFloat("circ_center_y", circ_pos.y);
	shader_.setFloat("circ_radius", radius);
}

void Shape::changeRadius(float radius)
{
	shader_.setFloat("circ_radius", radius);
}

void Shape::changePosCircle(vec3 pos)
{
	shader_.setFloat("circ_center_x", pos.x);
	shader_.setFloat("circ_center_y", pos.y);
}

void Shape::draw()
{
	shader_.use();
	glBindVertexArray(vaoID_);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

void Shape::changeSize(float new_width, float new_height)
{
	changeVertex(0, { vertices_[0].x = -new_width, vertices_[0].y, 0 }, colors_[0]);
	changeVertex(1, { 0, vertices_[1].y = new_height, 0 }, colors_[1]);
	changeVertex(2, { vertices_[2].x = new_width, vertices_[2].y, 0 }, colors_[2]);
}

void Shape::changePos(vec3 pos) {
	posMod.x = pos.x;
	posMod.y = pos.y;
	for (int i = 0; i < vertices_.size(); i++)
	{
		changeVertex(i, { vertices_[0].x + posMod.x, vertices_[i].y + posMod.y, 0 }, colors_[i]);
	}
}

void Shape::changeColor(vec3 color)
{
	for (int i = 0; i < vertices_.size(); i++)
	{
		changeVertex(i, vertices_[i], color);
		colors_[i] = color;
	}
}

Shape::~Shape()
{

}

std::vector<vec3> Shape::getVertices()
{
	auto ret{ vertices_ };

	for (auto& r : ret)
	{
		r.x += posMod.x;
		r.y += posMod.y;
		r.z += posMod.z;
	}

	return ret;
}

void Shape::addVertice(vec3 pos, vec3 color)
{
	std::vector<float> data{};
	vertices_.push_back(pos);
	colors_.push_back(color);
	//this data creation shit is very shit
	for (std::size_t i{}; i < vertices_.size(); i++)
	{
		data.push_back(vertices_[i].x);
		data.push_back(vertices_[i].y);
		data.push_back(vertices_[i].z);

		data.push_back(colors_[i].x);
		data.push_back(colors_[i].y);
		data.push_back(colors_[i].z);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vboID_);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Shape::removeVertice(int index)
{
	std::vector<float> data{};
	vertices_.erase(--vertices_.end());
	colors_.erase(--colors_.end());
	//this data creation shit is triggering me
	for (std::size_t i{}; i < vertices_.size(); i++)
	{

		data.push_back(vertices_[i].x);
		data.push_back(vertices_[i].y);
		data.push_back(vertices_[i].z);

		data.push_back(colors_[i].x);
		data.push_back(colors_[i].y);
		data.push_back(colors_[i].z);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vboID_);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Shape::clear()
{
	std::vector<float> data{};
	vertices_.clear();
	colors_.clear();

	glBindBuffer(GL_ARRAY_BUFFER, vboID_);
	glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}