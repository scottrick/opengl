#pragma once

#pragma comment(lib, "GLFW")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#pragma comment(lib, "glew32")
#pragma comment(lib, "SOIL")

class GLContext
{
public:
    GLContext();
    ~GLContext();

    void create();
    void destroy();

    void dumpExtensions();
    void dumpInfo();

protected:

private:

};
