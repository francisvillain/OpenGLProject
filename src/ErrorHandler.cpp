#include "ErrorHandler.h"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[Open error](" << error << "): " << function <<
            " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}
