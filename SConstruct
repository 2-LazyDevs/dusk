# Dusk only supports Linux for now & cross-platform support is planned for the future

import os

env = Environment(
    CXX='g++',
    CXXFLAGS='-std=c++17 -Wall -O2'
)


SRC_DIR = 'main'
CORE_DIR = 'core'
IO_DIR = os.path.join(CORE_DIR, 'io')
GLAD_DIR = 'thirdparty/glad'


env.Program(
    target='DuskEngine',
    source=[
        'main/main.cpp',
        'core/io/io.cpp',
        'editor/renderer/renderer.cpp',
        'thirdparty/glad/src/gl.c'
    ],
    CPPPATH=['core/io', 'main','editor/renderer', os.path.join(GLAD_DIR, 'include')],
    LIBS=['glfw', 'GL', 'pthread', 'dl', 'm', 'wayland-client', 'wayland-cursor', 'xkbcommon'],
    LIBPATH=['thirdparty/GLFW/lib']
)


