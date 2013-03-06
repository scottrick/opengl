#include "GLCameraScene.h"

#include "GLCamera.h"

GLCameraScene::GLCameraScene() 
{
    GLCamera *camera = new GLCamera();
    setCamera(camera);
    camera->Release();
}

GLCameraScene::~GLCameraScene() 
{
    setCamera(0);
}

const char *GLCameraScene::GetClassName() const 
{ 
    return "GLCameraScene";
}

void GLCameraScene::setCamera(GLCamera *camera) 
{
    if (pCamera != camera)
    {
        if (pCamera)
        {
            pCamera->Release();
            pCamera = 0;
        }

        if (camera) 
        {
            pCamera = camera;
            pCamera->AddRef();
        }
    }
}