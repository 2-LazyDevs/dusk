/**************************************************************************/
/*  main/main.cpp                                                         */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             DUSK ENGINE                                */
/*                         Licensed under the 2LD OSL                     */
/*   Copyright AR-DEV-1, 2LazyDevs & the DUSK contributors 2025-present   */
/**************************************************************************/

#include "main.h"
#include "../thirdparty/GLFW/include/glfw3.h"
#include <iostream>

namespace DUSK {
App::App(const std::string& title, int width, int height)
    : m_Title(title), m_Width(width), m_Height(height), m_IsRunning(false) {}

App::~App() = default;

bool App::Init() {
    std::cout << "Initializing Dusk \n";

    glfwSetErrorCallback([](int error, const char* description){
        std::cerr << "GLFW Error [" << error << "]: " << description << "\n";
    });

    if (!glfwInit()) {
        std::cerr << "GLFW Initialization failed. \n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // start with 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    if (!m_Window) {
        std::cerr << "Failed to create the window. \n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_Window));
    glfwSwapInterval(1);

    m_IsRunning = true;
    return true;
}


void App::Run() {
    while ((m_IsRunning) && !glfwWindowShouldClose(static_cast<GLFWwindow*>(m_Window)))
    {
        glfwPollEvents();

        // ToDo: Replace the update engine & render frame placeholders with actual functions
        // Update();
        // Render();

        glfwSwapBuffers(static_cast<GLFWwindow*>(m_Window));
    };
    
}

void App::Shutdown() {
    std::cout << "Shutting down Dusk \n";
    m_IsRunning = false;

    if (!m_Window) {
        glfwDestroyWindow(static_cast<GLFWwindow*>(m_Window));
        m_Window = NULL;
    };

    glfwTerminate();
}

} // namespace DUSK

int main() {
    DUSK::App app("Dusk engine", 1280, 720);

    if (!app.Init()) {
        std::cerr << "Failed to initialize Dusk!\n";
        return -1;
    }

    app.Run();
    app.Shutdown();

    return 0;
}
