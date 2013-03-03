#include "GLContext.h"

#include "GLScene.h"
#include "GLUtility.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <cassert>
#include <iostream>
using namespace std;

void idle();
void render();
void keyboardDown(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);

static bool bRunning = false;
static GLScene *pScene;

static unsigned int contextWindowWidth;
static unsigned int contextWindowHeight;

GLContext::GLContext() {

}

GLContext::~GLContext() {
    destroy();
}

void GLContext::create(int numArgs, char **args, char *windowName, unsigned int windowWidth, unsigned int windowHeight) {
	bRunning = true;
	contextWindowWidth = windowWidth;
	contextWindowHeight = windowHeight;

	//setup freeglut
	glutInit(&numArgs, args);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(contextWindowWidth, contextWindowHeight);
	glutInitWindowPosition(64, 64);

	if (windowName) {
		glutCreateWindow(windowName);
	}
	else {
		glutCreateWindow(args[0]);
	}

	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutDisplayFunc(render);
	glutIdleFunc(idle);
	
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	GLUtility::checkError();
	GLContext::dumpInfo();
}

void GLContext::go() {
	glutMainLoop();
}

void keyboardDown(unsigned char key, int x, int y) {
	cout << "keyboardDown " << (int)key << endl;
}

void keyboardUp(unsigned char key, int x, int y) {
	cout << "keyUp " << (int)key << endl;
	switch (key) {
	case 27: //ESC
		GLContext::destroy();
		break;
	default:
		break;
	}
}

void idle() {
	glutPostRedisplay();
}

void render() {
	GLUtility::checkError();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
	if (pScene) {
		pScene->prepareRender();
		pScene->render();
	}

	glutSwapBuffers();
}

void GLContext::destroy() 
{
	glutLeaveMainLoop();
	GLContext::setScene(0);
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

unsigned int GLContext::contextWidth() {
	return contextWindowWidth;
}

unsigned int GLContext::contextHeight() {
	return contextWindowHeight;
}

void GLContext::setScene(GLScene *scene) {
	if (pScene != scene) {
		if (pScene) {
			delete pScene;
			pScene = 0;
		}

		pScene = scene;
	}
}