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

void desenharEstrela(utils::MachineData& m)
{
    int minPos{ -100 };
    int maxPos{ 100 };
    int minRadius{ 1 };
    int maxRadius{ 10 };
    int minColor{ 0 };
    int maxColor{ 100 };

    float posX{ utils::randomFloat(minPos, maxPos) };
    float posY{ utils::randomFloat(minPos, maxPos) };
    float radius{ utils::randomFloat(minRadius,maxRadius) };
    float colorR{ utils::randomFloat(minColor, maxColor) };
    float colorG{ utils::randomFloat(minColor, maxColor) };
    float colorB{ utils::randomFloat(minColor, maxColor) };
    m.shapes_.push_back({ { posX, posY, 0 }, radius, { colorR, colorG, colorB } });
    m.shapesLight_.push_back({ { posX, posY, 0 }, radius, { 1.0f, 1.0f, 1.0f } });
    m.lines_[0].addVertice({ posX, posY, 0 }, { colorR, colorG, colorB });
    m.linesLight_[0].addVertice({ posX, posY, 0 }, { 1.0f, 1.0f, 1.0f });
}

utils::MachineData::MachineData(GLFWwindow* window)
    :shapes_{}, clear_color_{ 0.2f, 0.3f, 0.3f }, window_{ window }, lines_{}, linesLight_{}
{
    glClearColor(clear_color_.x, clear_color_.y, clear_color_.z, 1.0f);
    Line s{};
    Line s1{};
    lines_.push_back(s);
    linesLight_.push_back(s1);
    int minPos{ -100 };
    int maxPos{ 100 };
    int minRadius{ 1 };
    int maxRadius{ 10 };
    int minColor{ 0 };
    int maxColor{ 100 };

    for (int i = 0; i < 7; i++)
    {
        desenharEstrela(*this);
    }
}


/******          END STATE MACHINE SETTINGS          ******/



/******          BEGIN INPUT HANDLING           ******/


void  processInput(GLFWwindow* window, utils::MachineData& m);

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



    if (ImGui::IsKeyPressed(ImGuiKey_Q))
        show_window = !show_window;


    // input
    // -----
    processInput(m.window_, m);
}

float utils::randomFloat(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);

    int random_num = dist(gen);
    return (float)(random_num) / 100;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window, utils::MachineData& m )
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    static bool holdN{};

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && !holdN)
    {
        desenharEstrela(m);
        holdN = true;
    }

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE)
        holdN = false;


    static bool holdT{};
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && !holdT)
    {
        m.light_ = !m.light_;
        holdT = true;
    }

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE)
        holdT = false;

    static bool holdX{};
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && !holdX)
    {
        if (m.shapes_.size() > 0)
        {
            m.shapes_.erase(--m.shapes_.end());
            m.shapesLight_.erase(--m.shapesLight_.end());
            m.linesLight_[0].removeVertice(m.linesLight_[0].getVertices().size()-1);
            m.lines_[0].removeVertice(m.lines_[0].getVertices().size()-1);
        }
        holdX = true;
    }

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE)
        holdX = false;


    static bool holdR{};
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && !holdR)
    {
        m.shapes_.clear();
        m.shapesLight_.clear();
        m.linesLight_[0].clear();
        m.lines_[0].clear();

        holdR = true;
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE)
        holdR = false;

}


/******          END INPUT HANDLING           ******/



/******          BEGIN RENDERING DATA         ******/


void utils::render(MachineData& machine)
{
    // render   
    // ------


    //draw all shapes created
    if (machine.light_) {
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        for (auto& s : machine.shapesLight_)
            s.draw();

        for (auto& s : machine.linesLight_)
            s.draw();
    }
    else {
        glClearColor(machine.clear_color_.x, machine.clear_color_.y, machine.clear_color_.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto& s : machine.shapes_)
            s.draw();

        for (auto& s : machine.lines_)
            s.draw();
    }


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