/**************************************************************************/
/*  editor/renderer/renderer.cpp                                          */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             DUSK ENGINE                                */
/*                         Licensed under the 2LD OSL                     */
/*   Copyright AR-DEV-1, 2LazyDevs & the DUSK contributors 2025-present   */
/**************************************************************************/

// ToDo: Replace the renderer with a real one

#include "renderer.h"

namespace DK::Renderer {
   void Renderer::Init(int width, int height) {
        // Set the viewport
        glViewport(0, 0, width, height);
        glEnable(GL_DEPTH_TEST); // Enable depth testing
        glEnable(GL_BLEND); // Enable blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Clear color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        // ToDo: Load shaders here (vertex + fragment)

    }

    void Renderer::BeginFrame() {
        // Clear color & depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    const char* vertexShaderSrc = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aColor;

        out vec3 ourColor;

        void main() {
          gl_Position = vec4(aPos, 1.0);
          ourColor = aColor;
        }
    )";

    const char* fragmentShaderSrc = R"(
        #version 330 core
        in vec3 ourColor;
        out vec4 FragColor;

        void main() {
          FragColor = vec4(ourColor, 1.0);
        }
    )";

    unsigned int Renderer::CompileShader(const char* vertexSrc, const char* fragmentSrc) {
        unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexSrc, nullptr);
        glCompileShader(vertex);

        unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentSrc, nullptr);
        glCompileShader(fragment);

        unsigned int program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return program;
    }

    void Renderer::DrawTriangle() {
        Renderer::shaderProgram = Renderer::CompileShader(vertexShaderSrc, fragmentShaderSrc);

        float vertices[] = {
          0.0f,  0.5f, 0.0f, // top
         -0.5f, -0.5f, 0.0f, // left
          0.5f, -0.5f, 0.0f  // right
        };

        unsigned int VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }


    void Renderer::EndFrame(GLFWwindow* window) {
        // Swap buffers and poll input events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
