#pragma once

#pragma comment(lib, "GLFW")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#pragma comment(lib, "glew32")

#include <GL/glew.h>
#include <GL/glfw.h>
#include "../glm/glm.hpp"

#include "GLScene.h"

class GLContext
{
public:
    GLContext();
    ~GLContext();

    void create();
    void destroy();

    void dumpExtensions();
    void dumpInfo();

    GLScene *getScene();

protected:
	void checkError();

private:
    GLScene scene;

};
