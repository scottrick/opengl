#include "GLContext.h"

#include "GLShader.h"
#include "GLTextureFactory.h"

#pragma comment(lib, "GLFW")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#pragma comment(lib, "glew32")

#include <GL/glew.h>
#include <GL/glfw.h>
#include "glm/glm.hpp"

#include <cassert>
#include <ctime>
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

	checkError();
	dumpInfo();
	
	GLShader fragShader("shaders/basic.frag");
	GLShader vertShader("shaders/basic.vert");

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragShader.getShader());
	glAttachShader(shaderProgram, vertShader.getShader());
	
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// this setup is needed for EACH VertexArrayObject I want to use
	////////////////////////////////////////////////////////////////////////////////////////////////////
	float vertices[] = {
		-0.5f,  0.5f, 0.0f, 0.0f, 0.8f,
		 0.5f,  0.5f, 0.3f, 0.0f, 0.9f,
		 0.5f, -0.5f, 0.0f, 0.3f, 0.8f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.3f,
	};

	GLubyte indices[] = {
		2, 1, 0, //triangle 1
		3, 2, 0, //triangle 2
	};

	//create the vertex array ONE
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//setup the vertex buffer
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//setup the index buffer
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	GLint colorAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (2 * sizeof(float)));
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////

	while(glfwGetWindowParam(GLFW_OPENED))
	{
		checkError();

		if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) {
			break;
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

		glfwSwapBuffers();
	}

	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void GLContext::checkError() {
	GLenum error = glGetError();
	if (error) {
		cout << "glError: " << error << endl;
	}
}

void GLContext::destroy() 
{
    glfwTerminate();
}

void GLContext::dumpExtensions()
{
    const GLubyte* data = glGetString(GL_EXTENSIONS);
    unsigned int len = strlen((char*)data) + 1; // + 1 to copy the null terminator
    GLubyte* extensions = new GLubyte[len];
    
    memcpy(extensions, data, len);
    GLubyte* current = extensions;

    while (*current != '\0')
    {
        if (*current == ' ')
        {
            *current = '\n';
        }

        current++;
    }

    cout << "==================================================" << endl;
    cout << "GL_EXTENSIONS" << endl;
    cout << "==================================================" << endl; 
    cout << extensions << endl;
    cout << "==================================================" << endl; 

    delete[] extensions;
}

void GLContext::dumpInfo()
{
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* shaderLang = glGetString(GL_SHADING_LANGUAGE_VERSION);

    cout << "GL_VERSION:   " << version << endl;
    cout << "GL_RENDERER:  " << renderer << endl;
    cout << "GL_VENDOR:    " << vendor << endl;
    cout << "GL_SHADELANG: " << shaderLang << endl;
}
