#pragma once

#include "..\scottbase\unknown.h"
#include <GL/glew.h>

class GLCamera : public Unknown
{
public:
    GLCamera();

    //unknown
    const char *GetClassName() const;

    GLfloat fov;
    GLfloat cameraX, cameraY, cameraZ;
    GLfloat lookAtX, lookAtY, lookAtZ;
    GLfloat upDirX, upDirY, upDirZ;

protected:
    ~GLCamera();

};
