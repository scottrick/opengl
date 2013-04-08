#pragma once

#include "GLScene.h"

#include <GL/glew.h>

class GLCamera;

class GLCameraScene : public GLScene
{
public:
    GLCameraScene();

	//scene
	void render();
    void update(GLdouble time, GLdouble deltaTime);
	string getRenderDebugString() const;

	//unknown
    const char *getClassName() const;

protected:
    ~GLCameraScene();

    GLCamera *pCamera;
    void setCamera(GLCamera *camera);

private:

	unsigned int triangleCount;
};
