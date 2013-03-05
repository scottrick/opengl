#pragma once

#include "GLScene.h"

#include <GL/glew.h>

class GLCameraScene : public GLScene
{
public:
    GLCameraScene(void);
    ~GLCameraScene(void);

    virtual const char *GetClassName() const;

private:
    GLfloat x;
};

