/**************************************************************************/
/*  editor/renderer/renderer.h                                            */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             DUSK ENGINE                                */
/*                         Licensed under the 2LD OSL                     */
/*   Copyright AR-DEV-1, 2LazyDevs & the DUSK contributors 2025-present   */
/**************************************************************************/

// ToDo: Replace the renderer with a real one
#ifndef DUSK_RENDERER_H
#define DUSK_RENDERER_H

#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace DK::Renderer {

class Renderer {
public:
    void Init(int width, int height);
    void BeginFrame();
    void DrawTriangle(); // Temp func
    void EndFrame(GLFWwindow* window);
private:
    private:
    unsigned int shaderProgram;    // compiled shader program ID
    unsigned int VAO, VBO;         // vertex array & buffer
    unsigned int CompileShader(const char* vertexSrc, const char* fragmentSrc);
};
}

#endif // DUSK_RENDERER_H