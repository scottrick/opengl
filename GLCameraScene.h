#pragma once

#include "GLScene.h"

#include <GL/glew.h>

class GLCamera;

class GLCameraScene : public GLScene
{
public:
    GLCameraScene();

	void render();

    virtual const char *getClassName() const;

protected:
    ~GLCameraScene();

    GLCamera *pCamera;
    void setCamera(GLCamera *camera);

private:
};
