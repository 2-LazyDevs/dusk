/**************************************************************************/
/*  core/io/io.cpp                                                        */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             DUSK ENGINE                                */
/*                         Licensed under the 2LD OSL                     */
/*   Copyright AR-DEV-1, 2LazyDevs & the DUSK contributors 2025-present   */
/**************************************************************************/

#include <algorithm>

#include <GLFW/glfw3.h>
#include "io.h"


namespace DK::IO {
static WindowHandle s_Window = nullptr;

bool IO::key_state_current[MAX_KEYS] = { false };
bool IO::key_state_previous[MAX_KEYS] = { false };

bool IO::mouse_state_current[MAX_MOUSE_BUTTONS] = { false };
bool IO::mouse_state_previous[MAX_MOUSE_BUTTONS] = { false };

float IO::mouse_x = 0.0f;
float IO::mouse_y = 0.0f;

void IO::Init(WindowHandle Window) {
    s_Window = Window;
    
    for (int key = 0; key < MAX_KEYS; key++) {
        key_state_current[key] = false;
        key_state_previous[key] = false;
    }

    for (int button = 0; button < MAX_MOUSE_BUTTONS; button++) {
        mouse_state_current[button] = false;
        mouse_state_previous[button] = false;
    }

    mouse_x = 0;
    mouse_y = 0;
}

void IO::Update() {
    // Copy previous state
    std::copy(key_state_current, key_state_current + MAX_KEYS, key_state_previous);
    std::copy(mouse_state_current, mouse_state_current + MAX_MOUSE_BUTTONS, mouse_state_previous);

    GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(s_Window);

    // Poll keys
    glfwSetKeyCallback(glfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
     if (key >= 0 && key <= GLFW_KEY_LAST) {
        IO::key_state_current[key] = (action == GLFW_PRESS || action == GLFW_REPEAT);
        IO::key_state_previous[key] = (action == GLFW_PRESS);
       }
    });

    // Poll mouse buttons
    for (int b = 0; b < MAX_MOUSE_BUTTONS; b++) {
        mouse_state_current[b] = (glfwGetMouseButton(glfwWindow, b) == GLFW_PRESS);
    }

    // Poll mouse position
    double x, y;
    glfwGetCursorPos(glfwWindow, &x, &y);
    mouse_x = static_cast<float>(x);
    mouse_y = static_cast<float>(y);
}


bool IO::IsKeyDown(Key key) {
    int k = static_cast<int>(key);

    // Safety check to ensure k won't exceed MAX_KEYS & will not be less then 0
    if (k < 0 || k >= GLFW_KEY_LAST) {
        return false;
    }

    return key_state_current[k];
}

bool IO::IsKeyPressed(Key key) {
    int k = static_cast<int>(key);

    // Safety check to ensure k won't exceed MAX_KEYS & will not be less then 0
    if (k < 0 || k >= GLFW_KEY_LAST) {
        return false;
    }

    return key_state_current[k] && !key_state_previous[k];
}

bool IO::IsMouseDown(MouseButton button) {
    int b = static_cast<int>(button);

    return mouse_state_current[b];
}

void IO::GetMousePos(float &x, float &y) {
    x = mouse_x;
    y = mouse_y;
}

void IO::SetCursorMode(CursorMode mode) {
    GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(s_Window);
    int glfwMode = GLFW_CURSOR_NORMAL;
    switch (mode) {
        case CursorMode::Normal:
            glfwMode = GLFW_CURSOR_NORMAL;
            break;
        case CursorMode::Hidden:
            glfwMode = GLFW_CURSOR_HIDDEN;
            break;
        case CursorMode::Locked:
            glfwMode = GLFW_CURSOR_DISABLED;
            break;
    }
    glfwSetInputMode(glfwWindow, GLFW_CURSOR, glfwMode);
}
}