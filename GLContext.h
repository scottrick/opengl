#pragma once

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#pragma comment(lib, "glew32")
#pragma comment(lib, "SOIL")

class GLScene;

class GLContext
{
public:
    static void create(int numArgs, char **args, char *windowName, unsigned int windowWidth, unsigned int windowHeight);
    static void destroy();
	
	static void setScene(GLScene *scene);

	static void go();

    static void dumpExtensions();
    static void dumpInfo();

	static unsigned int contextWidth();
	static unsigned int contextHeight();

protected:

private:
    GLContext();
    ~GLContext();

};
