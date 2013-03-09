#include "GLColoredGeometry.h"

#include "GLShaderManager.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <cassert>
#include <iostream>
using namespace std;

GLColoredGeometry::GLColoredGeometry(GLfloat vertices[], GLuint numVertices, GLuint elements[], GLuint numElements)
{
    shaderProgram = GLShaderManager::Manager()->getShaderProgram("shaders/ColoredGeometry");

    //setup the vertex and element index buffers
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 6, vertices, GL_STATIC_DRAW);

    //setup ebo
    this->numElements = numElements;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numElements * sizeof(GLuint), elements, GL_STATIC_DRAW);
}

GLColoredGeometry::~GLColoredGeometry()
{

}

GLuint GLColoredGeometry::getShaderProgram() const 
{
    return shaderProgram;
}

void GLColoredGeometry::render() const 
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    GLint colorAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));

    GLuint modelTransformUniform = glGetUniformLocation(shaderProgram, "model");
    glm::mat4 modelTransform = glm::mat4(); //identity model transformation for now
    glUniformMatrix4fv(modelTransformUniform, 1, GL_FALSE, glm::value_ptr(modelTransform));

    glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}

const char *GLColoredGeometry::getClassName() const 
{
    return "GLColoredGeometry";
}