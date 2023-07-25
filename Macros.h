#pragma once

#include <GL/glew.h>
#include <signal.h>

#define ASSERT(x)                                                                                  \
    if (!(x))                                                                                      \
        raise(SIGTRAP);

#ifdef DEBUG
#define GLCall(x)                                                                                  \
    GLClearError();                                                                                \
    x;                                                                                             \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif