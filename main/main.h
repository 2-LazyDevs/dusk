/**************************************************************************/
/*  main/main.h                                                           */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             DUSK ENGINE                                */
/*                         Licensed under the 2LD OSL                     */
/*   Copyright AR-DEV-1, 2LazyDevs & the DUSK contributors 2025-present   */
/**************************************************************************/

#ifndef DUSK_MAIN_H
#define DUSK_MAIN_H

#pragma once

#include <string>

namespace DK::Main {

class App {
public:
    App(const std::string& title, int width, int height);
    ~App();

    bool Init();

    void Run();

    void Shutdown();

private:
    std::string m_Title;
    int m_Width;
    int m_Height;

    bool m_IsRunning;

    void* m_Window;

  };
} // namespace DUSK
#endif // DUSK_MAIN_H