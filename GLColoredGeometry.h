#pragma once

#include "GLRenderable.h"
#include <GL/glew.h>

class GLColoredGeometry : public GLRenderable
{
public:
    GLColoredGeometry(GLfloat vertices[], GLuint numVertices, GLuint elements[], GLuint numElements);

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

    GLuint numElements;

};

