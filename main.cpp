#include "GLContext.h"

/* 
	OpenGL boilerplate setup.  Requires GLEW, GLFW, and SOIL; also uses GLM.
*/
int main (int numArgs, char **args) {
	GLContext context = GLContext();
	context.create();
}