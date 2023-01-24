#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/ShaderProgram.hpp"
#include <iostream>

void AbstractMaterial::GLErrorHandeling(std::string nameOfValue)
{
    GLenum error = glGetError();
    std::cout << nameOfValue << ": ";

    if (error) {
        std::cout << error << '\n';
        return;
    }
    else {
        std::cout << "no error" << '\n';
    }
}

AbstractMaterial::AbstractMaterial()
{
    //ctor
}

AbstractMaterial::~AbstractMaterial()
{
    //dtor
}

