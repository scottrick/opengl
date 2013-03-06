#pragma once

#include "GLScene.h"

#include <GL/glew.h>

class GLCamera;

class GLCameraScene : public GLScene
{
public:
    GLCameraScene();

    virtual const char *GetClassName() const;

protected:
    ~GLCameraScene();

    GLCamera *pCamera;
    void setCamera(GLCamera *camera);

private:
};
