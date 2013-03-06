#pragma once

#include "GLScene.h"

#include <GL/glew.h>

class GLCamera;
class GLRenderable;

class GLCameraScene : public GLScene
{
public:
    GLCameraScene();

	void render();

    virtual const char *GetClassName() const;

protected:
    ~GLCameraScene();

    GLCamera *pCamera;
    void setCamera(GLCamera *camera);

    GLRenderable *pRenderable;

private:
};
