/**************************************************************************/
/*  main/main.cpp                                                         */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             DUSK ENGINE                                */
/*                         Licensed under the 2LD OSL                     */
/*   Copyright AR-DEV-1, 2LazyDevs & the DUSK contributors 2025-present   */
/**************************************************************************/

#include <iostream>

#include "main.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "io.h"

namespace DK::Main {

using namespace DK::IO;
using namespace DK::Renderer;

App::App(const std::string& title, int width, int height)
    : m_Title(title), m_Width(width), m_Height(height), m_IsRunning(false) {}

App::~App() = default;

bool App::Init() {
    std::cout << "Initializing Dusk \n";

    glfwSetErrorCallback([](int error, const char* description){
        std::cerr << "GLFW Error [" << error << "]: " << description << "\n Report this error here: https://github.com/2-LazyDevs/dusk/issues \n";
    });

    if (!glfwInit()) {
        std::cerr << "GLFW Initialization failed. Report this error here: https://github.com/2-LazyDevs/dusk/issues \n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    if (!m_Window) {
        std::cerr << "Failed to create the window. Report this error here: https://github.com/2-LazyDevs/dusk/issues \n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_Window));
    glfwSwapInterval(1);

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "The OpenGL loader, GLAD, failed. Report this error here: https://github.com/2-LazyDevs/dusk/issues \n";
        return -1;
    }
    
    std::cout << "The OpenGL version is: " << glGetString(GL_VERSION) << "\n";

    IO::IO::Init(m_Window);

    m_IsRunning = true;
    return true;
}


bool App::Run() {
    // Create & init the renderer
    Renderer::Renderer renderer;
    renderer.Init(800, 600);

    bool userExit = false;
    while ((m_IsRunning) && !glfwWindowShouldClose(static_cast<GLFWwindow*>(m_Window)))
    {
        glfwPollEvents();

        // ToDo: Replace the update engine & render frame placeholders with actual functions
        // Update();

        renderer.BeginFrame();

        renderer.DrawTriangle();

        renderer.EndFrame(static_cast<GLFWwindow*>(m_Window));

        IO::IO::Update();

        if(IO::IO::IsKeyPressed(Key::Escape)) {
            m_IsRunning = false;
            userExit = true;
        }

        glfwSwapBuffers(static_cast<GLFWwindow*>(m_Window));
    };
    
    return !userExit;
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
    DK::Main::App app("Dusk engine", 1280, 720);

    if (!app.Init()) {
        std::cerr << "Failed to initialize Dusk! Report this error here: https://github.com/2-LazyDevs/dusk/issues \n";
        return -1;
    }

    bool success = app.Run();
    app.Shutdown();

    return success ? 0 : -1;
}
