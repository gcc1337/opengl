#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <vector>

#include "shader.hpp"
#include "shape.hpp"
#include "utils.hpp"

int main()
{
    auto window = utils::configure("Gustavo Carvalho cunha", 720, 720);
    if (window == nullptr) {
        std::cout << "Window creation failed!\n";
        return -1;
    }
    
    utils::MachineData machine{ window };

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        utils::handle_input(machine);
        utils::render(machine);
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // --------------------------- ---------------------------------------------
    //glDeleteVertexArrays(1, VAO.data());
    //glDeleteBuffers(1, VBO.data());
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}