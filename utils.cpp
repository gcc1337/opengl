#include "utils.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <random>


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
    :vertices_{}, shaders_{}, shapes_{}, colors_{}, window_{window}, clear_color_{ 0.2f, 0.3f, 0.3f }
{
    //shader creation
    shaders_.push_back(Shader{ "vertexShader.vs", "fragmentShader.fs" });

    //simple square
    vertices_ = { {-0.1f, -0.4f, 0.0f},
                  {-0.6f,  0.4f, 0.0f},
                  { 0.4f, -0.4f, 0.0f},
                  { 0.4f,  0.4f, 0.0f} };

    colors_.push_back({ 0.5f, 0.5f, 0.0f });

    shapes_.push_back({ vertices_, colors_[0]});

    glClearColor(clear_color_.x, clear_color_.y, clear_color_.z, 1.0f);
}


/******          END STATE MACHINE SETTINGS          ******/



/******          BEGIN INPUT HANDLING           ******/


void  processInput(GLFWwindow* window, vec3& rgb, vec3& rgb_b);

void utils::handle_input(MachineData& m)
{
    //imgui 
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //gui auxiliar variables
    static bool show_window{ false };
    static float aux_width = 0.5f;
    static float aux_height = 0.5f;
    static vec3 aux_rgb = { m.colors_[0] };

    //gui creation
    if (show_window) 
    {
        ImGui::Begin("Retangulo", &show_window);
        ImGui::DragFloat("Largura", &aux_width, 0.005f, 0.0f, 1.0f, "%.3f");
        ImGui::DragFloat("Altura", &aux_height, 0.005f, 0.0f, 1.0f, "%.3f");
        ImGui::ColorEdit3("Cor retangulo", &aux_rgb.x);
        ImGui::ColorEdit3("Cor background", &m.clear_color_.x);
        ImGui::End();
    }

    if (ImGui::IsKeyPressed(ImGuiKey_Q))
        show_window = !show_window;

    //change vector position and color
    m.shapes_[0].changeVertex(0, { -aux_width, -aux_height, 0 }, aux_rgb);
    m.shapes_[0].changeVertex(1, { -aux_width, aux_height, 0 }, aux_rgb);
    m.shapes_[0].changeVertex(2, { aux_width, -aux_height, 0 }, aux_rgb);
    m.shapes_[0].changeVertex(3, { aux_width, aux_height, 0 }, aux_rgb);

    // input
    // -----
    processInput(m.window_, aux_rgb, m.clear_color_);
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
void processInput(GLFWwindow* window, vec3& rbg, vec3& rgb_b)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    static bool pressed{ false };
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !pressed)
    {
        rbg = vec3{ randomFloat(),randomFloat(),randomFloat() };
        rgb_b = vec3{ randomFloat(),randomFloat(),randomFloat() };
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

    machine.shaders_[0].use();
    machine.shapes_[0].draw();
    
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