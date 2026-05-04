#include "utils.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <random>

#include "line.hpp"
#include <format>


/******          BEGIN CONFIGURATION SETTINGS          ******/


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow* utils::configure(std::string window_title, int window_width, int window_height)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_title.data(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    // glfw callback configurations
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    // imGui config
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    return window;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


/******          END CONFIGURATION SETTINGS          ******/



/******          BEGIN STATE MACHINE SETTINGS          ******/


utils::MachineData::MachineData(GLFWwindow* window)
    :shapes_{}, clear_color_{ 0.2f, 0.3f, 0.3f }, window_{ window }
{
    glClearColor(clear_color_.x, clear_color_.y, clear_color_.z, 1.0f);

    std::vector<vec3> verticesTriangle_ = { {-1.0f , 0, 0.0f},
                                            {0, 1.0f , 0.0f },
                                            {1.0f , 0 , 0.0f } };
    for (int i = 0; i < 5; i++)
    {
        shapes_.push_back({ verticesTriangle_, { i / 10.0f, i / 10.0f, i / 10.0f } });
        
    }

    std::vector<vec3> points1{ {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f} };
    lines_.push_back({ points1, { 1.0f, 1.0f, 1.0f } });

    std::vector<vec3> points2{ {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f} };
    lines_.push_back({ points2, { 1.0f, 1.0f, 1.0f } });

}


/******          END STATE MACHINE SETTINGS          ******/



/******          BEGIN INPUT HANDLING           ******/


void  processInput(GLFWwindow* window, vec3& rgb_b);

void utils::handle_input(MachineData& m)
{
    //imgui 
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //gui auxiliar variables
    static bool show_window{ false };
    static std::vector<float> aux_width(5, 0.1f);
    static std::vector<float> aux_height(5, 0.190f);
    static std::vector<float> aux_x{ -0.715f, -0.305f, 0.615f, 0.615f, -0.715f };
    static std::vector<float> aux_y{ 0.635f, 0.635f, 0.635f, -0.550f, -0.550 };
    static std::vector<vec3> aux_rgb(5);

    //gui creation
    if (show_window) 
    {
        ImGui::Begin("Retangulo", &show_window);
        for (int i = 0; i < 5; i++)
        {
            ImGui::PushID(i);
            ImGui::Text("Retangulo %i", i);
            ImGui::DragFloat("Largura", &aux_width[i], 0.005f, 0.0f, 1.0f, "%.3f");
            ImGui::DragFloat("Altura", &aux_height[i], 0.005f, 0.0f, 1.0f, "%.3f");
            ImGui::DragFloat("X", &aux_x[i], 0.005f, -1.0f, 1.0f, "%.3f");
            ImGui::DragFloat("Y", &aux_y[i], 0.005f, -1.0f, 1.0f, "%.3f");
            ImGui::ColorEdit3("Cor retangulo", &aux_rgb[i].x);
            ImGui::PopID();
        }

        ImGui::ColorEdit3("Cor background", &m.clear_color_.x);

        ImGui::End();
    } 

    std::vector<ImVec2> textPos{
        {0,300},
        {180,300},
        {500,300},
        {500,600},
        { 0,600 },
    };



    if (ImGui::IsKeyPressed(ImGuiKey_Q))
        show_window = !show_window;

    for (int i = 0; i < 5; i++)
    {
        m.shapes_[i].changeColor(aux_rgb[i]);
        m.shapes_[i].changeSize(aux_width[i], aux_height[i]);
        m.shapes_[i].changePosTriangle({ aux_x[i], aux_y[i], 0.0f });
    }

    for (int i = 0; i < 5; i++)
    {
        auto v{ m.shapes_[i].getVertices() };
        ImGui::GetBackgroundDrawList()->AddText(
            textPos[i],
            IM_COL32(255, 255, 255, 255),
            std::format("Retangulo {}:\n "
                "V[{}]: {}, {}\n"
                "V[{}]: {}, {}\n"
                "V[{}]: {}, {}\n", i, 1, v[0].x, v[0].y, 2, v[1].x, v[1].y, 3, v[2].x, v[2].y
                , i, aux_x[i], aux_y[i]).data()
        );
    }


    // input
    // -----
    processInput(m.window_, m.clear_color_);
}

float randomFloat()
{
    std::random_device rd;
    std::mt19937 gen(rd());  
    std::uniform_int_distribution<> dist(1, 100);

    int random_num = dist(gen);
    return (float)(random_num) / 100;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window, vec3& rgb_b)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    static bool pressed{ false };
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !pressed)
    {
        //rbg = vec3{ randomFloat(),randomFloat(),randomFloat() };
        //rgb_b = vec3{ randomFloat(),randomFloat(),randomFloat() };
        pressed = true ;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
        pressed = false;
}



/******          END INPUT HANDLING           ******/



/******          BEGIN RENDERING DATA         ******/


void utils::render(MachineData& machine)
{
    // render   
    // ------

    glClearColor(machine.clear_color_.x, machine.clear_color_.y, machine.clear_color_.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //draw all shapes created
    for(auto& s : machine.shapes_)
        s.draw();

    for (auto& s : machine.lines_)
        s.draw();

    //imgui endings
    // Rendering
    // (Your code clears your framebuffer, renders your other stuff etc.)
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // (Your code calls glfwSwapBuffers() etc.)

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(machine.window_);
    glfwPollEvents();
}


/******          END RENDERING DATA         ******/