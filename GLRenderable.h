#pragma once

#include "..\scottbase\unknown.h"
#include <GL/glew.h>

class GLRenderable : public Unknown
{
public:
    GLRenderable();

    virtual void render() const = 0;
    virtual GLuint getShaderProgram() const = 0;

protected:
    ~GLRenderable();

};

