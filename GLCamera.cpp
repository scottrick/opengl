#include "GLCamera.h"

GLCamera::GLCamera()
{
    fov = 45.0f;
    cameraX = 4.0f;
    cameraY = 2.0f;
    cameraZ = 1.5f;
    lookAtX = 0.0f;
    lookAtY = 0.0f;
    lookAtZ = 0.0f;
    upDirX = 0.0f;
    upDirY = 0.0f;
    upDirZ = 1.0f;
}

GLCamera::~GLCamera()
{

}

const char *GLCamera::GetClassName() const 
{
    return "GLCamera";
}
