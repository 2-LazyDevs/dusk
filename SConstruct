# Dusk only supports Linux for now & cross-platform support is planned for the future

import os

env = Environment(
    CXX='g++',
    CXXFLAGS='-std=c++17 -Wall -O2'
)


SRC_DIR = 'main'
CORE_DIR = 'core'
IO_DIR = os.path.join(CORE_DIR, 'io')

engine_sources = [
    os.path.join(SRC_DIR, 'main.cpp'),
    os.path.join(IO_DIR, 'io.cpp'),
]

all_sources = engine_sources

include_paths = [
    IO_DIR,
    SRC_DIR,
]
env.Append(CPPPATH=include_paths)


env.Program(
    target='DuskEngine',
    source=[
        'main/main.cpp',
        'core/io/io.cpp'
    ],
    CPPPATH=['core/io', 'main'],
    LIBS=['glfw', 'GL', 'pthread', 'dl', 'm', 'wayland-client', 'wayland-cursor', 'xkbcommon'],
    LIBPATH=['thirdparty/GLFW/lib']
)


