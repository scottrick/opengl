#include "GLContext.h"

#include <cassert>
#include <iostream>
using namespace std;

GLContext::GLContext()
{

}

GLContext::~GLContext()
{
    destroy();
}

void GLContext::create() 
{
	glfwInit();

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow(800, 600, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);
	glfwSetWindowTitle("OpenGL");

	glewExperimental = GL_TRUE;
	glewInit();

	while( glfwGetWindowParam( GLFW_OPENED ) )
	{
		if ( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS )
			break;

		glfwSwapBuffers();
	}
}

void GLContext::destroy() 
{
    glfwTerminate();
}

void GLContext::dumpExtensions()
{
    //const GLubyte* data = glGetString(GL_EXTENSIONS);
    //unsigned int len = strlen((char*)data) + 1; //+1 to copy the null terminator
    //GLubyte* extensions = new GLubyte[len];
    //
    //memcpy(extensions, data, len);
    //GLubyte* current = extensions;

    //while (*current != '\0')
    //{
    //    if (*current == ' ')
    //    {
    //        *current = '\n';
    //    }

    //    current++;
    //}

    //cout << "==================================================" << endl;
    //cout << "GL_EXTENSIONS" << endl;
    //cout << "==================================================" << endl; 
    //cout << extensions << endl;
    //cout << "==================================================" << endl; 

    //delete[] extensions;
}

void GLContext::dumpInfo()
{
    //const GLubyte* version = glGetString(GL_VERSION);
    //const GLubyte* renderer = glGetString(GL_RENDERER);
    //const GLubyte* vendor = glGetString(GL_VENDOR);
    //const GLubyte* shaderLang = glGetString(GL_SHADING_LANGUAGE_VERSION);

    //cout << "GL_VERSION:   " << version << endl;
    //cout << "GL_RENDERER:  " << renderer << endl;
    //cout << "GL_VENDOR:    " << vendor << endl;
    //cout << "GL_SHADELANG: " << shaderLang << endl;
}

GLScene *GLContext::getScene()
{
    return &scene;
}