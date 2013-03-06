#pragma once

#include "GLRenderable.h"
#include <GL/glew.h>

class GLColoredGeometry : public GLRenderable
{
public:
    GLColoredGeometry(GLfloat *vertices, unsigned int *elements, unsigned int count);

    //renderable
    void render() const;
    GLuint getShaderProgram() const;

    //unknown
    const char *GetClassName() const;

protected:
    ~GLColoredGeometry();

    GLuint shaderProgram;

    GLuint vbo;
    GLuint ebo;

};

