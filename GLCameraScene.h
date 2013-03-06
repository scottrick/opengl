#pragma once

#include "GLScene.h"

#include <GL/glew.h>

class GLCameraScene : public GLScene
{
public:
    GLCameraScene();

    virtual const char *GetClassName() const;

protected:
    ~GLCameraScene();

private:
    GLfloat x;
};

