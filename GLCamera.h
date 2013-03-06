#pragma once

#include "..\scottbase\unknown.h"
#include <GL/glew.h>

class GLCamera : public Unknown
{
public:
    GLCamera();

    //unknown
    const char *GetClassName() const;

protected:
    ~GLCamera();

    GLfloat fov;
    GLfloat cameraX, cameraY, cameraZ;
    GLfloat lookAtX, lookAtY, lookAtZ;
    GLfloat upDirX, upDirY, upDirZ;
};

//glm::mat4 proj = glm::perspective( 45.0f, (float)GLContext::contextWidth() / (float)GLContext::contextHeight(), 1.0f, 10.0f );
//glUniformMatrix4fv(projTransformUniform, 1, GL_FALSE, glm::value_ptr(proj));
//
//glm::mat4 view = glm::lookAt(
//	glm::vec3(4.0f, 0.0f, 1.5f),
//	glm::vec3(0.0f, 0.0f, 0.0f),
//	glm::vec3(0.0f, 0.0f, 1.0f)
//);
//glUniformMatrix4fv(viewTransformUniform, 1, GL_FALSE, glm::value_ptr(view));
