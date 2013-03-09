#include "GLCamera.h"

GLCamera::GLCamera()
{
    fov = 45.0f;
    cameraX = 10.0f;
    cameraY = 10.5f;
    cameraZ = 23.0f;
    lookAtX = 0.0f;
    lookAtY = 0.0f;
    lookAtZ = 0.0f;
    upDirX = 0.0f;
    upDirY = 1.0f;
    upDirZ = 0.0f;
}

GLCamera::~GLCamera()
{

}

const char *GLCamera::getClassName() const 
{
    return "GLCamera";
}
