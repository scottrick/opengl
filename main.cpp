#include <iostream>

#include "opengl\GLContext.h"

/* 
	OpenGL boilerplate setup.  Requires GLEW and GLFW, and uses GLM.
*/
int main (int numArgs, char **args) {
	GLContext context = GLContext();
	context.create();
}