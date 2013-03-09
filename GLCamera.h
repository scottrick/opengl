#pragma once

#include "..\scottbase\unknown.h"
#include "glm/glm.hpp"
#include <GL/glew.h>

class GLCamera : public Unknown
{
public:
    GLCamera();

    void update(GLdouble time, GLdouble deltaTime);

    //unknown
    const char *getClassName() const;

    GLfloat speed;

    GLfloat fov;
    glm::vec3 pos;
    glm::vec3 lookDir;
    glm::vec3 upDir;

protected:
    ~GLCamera();

};
