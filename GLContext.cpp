#include "GLContext.h"

#include "GLShader.h"
#include "GLTexture.h"
#include "GLTextureFactory.h"
#include "GLUtility.h"

#include <GL/glew.h>
#include <GL/glfw.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <cassert>
#include <ctime>
#include <iostream>
using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

bool bRunning = false;
void GLFWCALL keyboardCallback(int key, int action);

GLContext::GLContext()
{

}

GLContext::~GLContext()
{
    destroy();
}

void GLContext::create() 
{
	bRunning = true;

	glfwInit();

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0, 0, 24, 8, GLFW_WINDOW);
	glfwSetWindowTitle("OpenGL");

	glfwSetKeyCallback(keyboardCallback);

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	GLUtility::checkError();
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
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		-1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
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

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	GLint colorAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));

	GLint textureAttrib = glGetAttribLocation(shaderProgram, "texture");
	glEnableVertexAttribArray(textureAttrib);
	glVertexAttribPointer(textureAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////

	GLTexture *textureOne = GLTextureFactory::createTextureForImage("hobbes.png");
	GLTexture *textureTwo = GLTextureFactory::createTextureForImage("test_texture.png");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureOne->getTexture());
	glUniform1i(glGetUniformLocation(shaderProgram, "textureOne"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureTwo->getTexture());
	glUniform1i(glGetUniformLocation(shaderProgram, "textureTwo"), 1);

	GLuint timeUniform = glGetUniformLocation(shaderProgram, "time");
	GLuint overrideColorUniform = glGetUniformLocation(shaderProgram, "overrideColor");
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	GLuint modelTransformUniform = glGetUniformLocation(shaderProgram, "model");
	GLuint viewTransformUniform = glGetUniformLocation(shaderProgram, "view");
	GLuint projTransformUniform = glGetUniformLocation(shaderProgram, "proj");

	glm::mat4 proj = glm::perspective( 45.0f, (float)WINDOW_WIDTH / (float)	WINDOW_HEIGHT, 1.0f, 10.0f );
	glUniformMatrix4fv(projTransformUniform, 1, GL_FALSE, glm::value_ptr(proj));

	glm::mat4 view = glm::lookAt(
		glm::vec3(4.0f, 0.0f, 1.5f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
	glUniformMatrix4fv(viewTransformUniform, 1, GL_FALSE, glm::value_ptr(view));

	while (glfwGetWindowParam(GLFW_OPENED))
	{
		GLUtility::checkError();

		if (!bRunning) {
			break;
		}

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
		GLfloat time = ((float)clock() / (float)CLOCKS_PER_SEC);
		glUniform1f(timeUniform, time);

		glm::mat4 modelTransform;
		modelTransform = glm::rotate(modelTransform, time * 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelTransformUniform, 1, GL_FALSE, glm::value_ptr(modelTransform));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////
		glEnable( GL_STENCIL_TEST );

			// Draw floor
			glStencilFunc( GL_ALWAYS, 1, 0xFF );
			glStencilOp( GL_KEEP, GL_KEEP, GL_REPLACE );
			glStencilMask( 0xFF );

			glDepthMask( GL_FALSE );
			glClear(GL_STENCIL_BUFFER_BIT);
			glDrawArrays( GL_TRIANGLES, 36, 6 );

			//// Draw cube reflection
			glStencilFunc( GL_EQUAL, 1, 0xFF );
			glStencilMask( 0x00 );
			glDepthMask( GL_TRUE );

			modelTransform = glm::scale( glm::translate( modelTransform, glm::vec3( 0, 0, -1 ) ), glm::vec3( 1, 1, -1 ) );
			glUniformMatrix4fv( modelTransformUniform, 1, GL_FALSE, glm::value_ptr( modelTransform ) );

			glUniform3f(overrideColorUniform, 0.3f, 0.3f, 0.3f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glUniform3f(overrideColorUniform, 1.0f, 1.0f, 1.0f);

		glDisable( GL_STENCIL_TEST );
		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////

		glfwSwapBuffers();
	}

	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	delete textureOne;
	delete textureTwo;
}

void GLFWCALL keyboardCallback(int key, int action)
{
	if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) {
		bRunning = false;
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
