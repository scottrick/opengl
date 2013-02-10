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

bool bDoFlip = false;
float flipDuration = 0.6f;
float flipStartTime = -flipDuration;

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
	glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);
	glfwSetWindowTitle("OpenGL");

	glfwSetKeyCallback(keyboardCallback);

	glewExperimental = GL_TRUE;
	glewInit();

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
		-0.8f,  0.8f, 0.0f, 0.0f, 0.8f, 0.0f, 0.0f, //top left
		 0.8f,  0.8f, 0.3f, 0.0f, 0.9f, 1.0f, 0.0f, //top right
		 0.8f, -0.8f, 0.0f, 0.3f, 0.8f, 1.0f, 1.0f, //bottom right
		-0.8f, -0.8f, 0.0f, 0.0f, 0.3f, 0.0f, 1.0f, //bottom left
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
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

	GLint colorAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) (2 * sizeof(float)));

	GLint textureAttrib = glGetAttribLocation(shaderProgram, "texture");
	glEnableVertexAttribArray(textureAttrib);
	glVertexAttribPointer(textureAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) (5 * sizeof(float)));
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

	GLuint ratioUniform = glGetUniformLocation(shaderProgram, "time");

	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	GLuint modelTransformUniform = glGetUniformLocation(shaderProgram, "model");
	GLuint viewTransformUniform = glGetUniformLocation(shaderProgram, "view");
	GLuint projTransformUniform = glGetUniformLocation(shaderProgram, "proj");

	glm::mat4 proj = glm::perspective( 45.0f, (float)WINDOW_WIDTH / (float)	WINDOW_HEIGHT, 1.0f, 10.0f );
	glUniformMatrix4fv(projTransformUniform, 1, GL_FALSE, glm::value_ptr(proj));

	while (glfwGetWindowParam(GLFW_OPENED))
	{
		GLUtility::checkError();

		if (!bRunning) {
			break;
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat time = ((float)clock() / (float)CLOCKS_PER_SEC);
		glUniform1f(ratioUniform, time);

		if (bDoFlip) {
			bDoFlip = false;
			flipStartTime = time;
		}

		glm::mat4 modelTransform;
		modelTransform = glm::rotate(modelTransform, time * 18.0f, glm::vec3(0.0f, 0.0f, 1.0f));

		if (time < flipStartTime + flipDuration) {
			modelTransform = glm::rotate(modelTransform, (time - flipStartTime) * (360.0f / flipDuration), glm::vec3(1.0f, 0.0f, 0.0f));
		}

		glUniformMatrix4fv(modelTransformUniform, 1, GL_FALSE, glm::value_ptr(modelTransform));

		float distance = 1.2f + (sin(time * 2.0f) + 1.0f) * 2.0f;
		glm::mat4 view = glm::lookAt(
			glm::vec3( distance, distance, distance ),
			glm::vec3( 0.0f, 0.0f, 0.0f ),
			glm::vec3( 0.0f, 0.0f, 1.0f )
		);
		glUniformMatrix4fv(viewTransformUniform, 1, GL_FALSE, glm::value_ptr(view));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

		glfwSwapBuffers();
	}

	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &ebo);
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
	else if (glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS) {
		bDoFlip = true;
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
