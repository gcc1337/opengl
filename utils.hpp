#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shape.hpp"
#include "shader.hpp"
#include "line.hpp"

namespace utils
{
	GLFWwindow* configure(std::string window_title = "generic", int window_width = 800, int window_height = 600);

	struct MachineData
	{
		MachineData(GLFWwindow* window);

		bool light_{ false };
		std::vector<Shape> shapes_{};
		std::vector<Shape> shapesLight_{};
		std::vector<Line> lines_{};
		std::vector<Line> linesLight_{};
		vec3 clear_color_{};

		GLFWwindow* window_{};
	};


	void handle_input(MachineData& machine);

	void render(MachineData& machine);

	float randomFloat(int min, int max);


}