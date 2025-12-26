/**************************************************************************/
/*  core/io/io.h                                                       */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             DUSK ENGINE                                */
/*                         Licensed under the 2LD OSL                     */
/*   Copyright AR-DEV-1, 2LazyDevs & the DUSK contributors 2025-present   */
/**************************************************************************/

#ifndef DUSK_IO_H
#define DUSK_IO_H

#pragma once

#include <cstdint>
#include <utility>

namespace DK::IO {
static constexpr int MAX_KEYS = 105;
static constexpr int MAX_MOUSE_BUTTONS = 8;

using WindowHandle = void*;

enum class Key : uint16_t {
    Unknown = 0,
    A, B, C, D, E, F, G,
    H, I, J, K, L, M, N,
    O, P, Q, R, S, T,
    U, V, W, X, Y, Z,
    Escape,
    LeftShift,
    RightShift,
    LeftCtrl,
    RightCtrl,
    Enter
};

enum class MouseButton : uint8_t {
    Left = 0,
    Right,
    Middle
};

enum class CursorMode {
    Normal,
    Hidden,
    Locked
};

class IO {
public:
    static void Init(WindowHandle window);
    static void Update();

    static bool IsKeyDown(Key key);
    static bool IsKeyPressed(Key key);

    static bool IsMouseDown(MouseButton button);

    static void GetMousePos(float& x, float& y);
    static void SetCursorMode(CursorMode mode);

private:
    static WindowHandle s_WindowHandle;

    static bool key_state_current[MAX_KEYS];
    static bool key_state_previous[MAX_KEYS];

    static bool mouse_state_current[MAX_MOUSE_BUTTONS];
    static bool mouse_state_previous[MAX_MOUSE_BUTTONS];

    static float mouse_x;
    static float mouse_y;
};

} // namespace DK::IO

#endif
