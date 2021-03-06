#include "GLContext.h"

#include "GLScene.h"
#include "Input.h"
#include "Utility.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <cassert>
#include <sstream>
#include <iostream>
using namespace std;

void idle();
void render();
void keyboardDown(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void mouseMoveActive(int x, int y);
void mouseMovePassive(int x, int y);
void reshape(int width, int height);

static bool bRunning = false;
static bool bDrawInfo = false;
static GLScene *pScene;

static unsigned int contextWindowWidth;
static unsigned int contextWindowHeight;

static GLdouble appStartTime = 0.0;
static GLdouble previousTime = 0.0;
static GLdouble currentTime = 0.0;

static GLuint framesThisSecond = 0;
static GLuint framesLastSecond = 0;
static GLdouble fpsLastSecondTime = 0.0;

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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(contextWindowWidth, contextWindowHeight);
	glutInitWindowPosition(320, 32);

	if (windowName) {
		glutCreateWindow(windowName);
	}
	else {
		glutCreateWindow(args[0]);
	}

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutDisplayFunc(render);
	glutIdleFunc(idle);
    glutReshapeFunc(reshape);

    glutMotionFunc(mouseMoveActive);
    glutPassiveMotionFunc(mouseMovePassive);
    glutSetCursor(GLUT_CURSOR_NONE);

    //reset the mouse
    glutWarpPointer(contextWindowWidth / 2, contextWindowHeight / 2);
	
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		const GLubyte *error = glewGetErrorString(err);
		cout << "glewInit error: " << error << endl;
		destroy();
		return;
	}

	glEnable(GL_DEPTH_TEST);

	Utility::checkError();
	GLContext::dumpInfo();
}

void GLContext::go() {
    appStartTime = Utility::getSystemTime();
	glutMainLoop();
}

void updateModifiers()
{
    GLulong modifiers = 0;
    if (glutGetModifiers() & GLUT_ACTIVE_SHIFT) 
    {
        modifiers |= INPUT_MODIFIER_SHIFT;
    }
    if (glutGetModifiers() & GLUT_ACTIVE_CTRL)
    {
        modifiers |= INPUT_MODIFIER_CONTROL;
    }
    if (glutGetModifiers() & GLUT_ACTIVE_ALT)
    {
        modifiers |= INPUT_MODIFIER_ALT;
    }
    Input::sharedInput()->setModifiers(modifiers);
}

void keyboardDown(unsigned char key, int x, int y) {
	//cout << "keyboardDown " << (int)key << endl;
    Input::sharedInput()->inputDown(key);
    updateModifiers();

    switch (key) {
    case 27: //ESC
        GLContext::destroy();
        break;
    case 6: //CTRL + f
        bDrawInfo = !bDrawInfo;
        break;
    case 13: //ENTER
        if (Input::sharedInput()->getKeyboardModifierFlags() & INPUT_MODIFIER_ALT)
        {
            glutFullScreenToggle();
        }
        break;
    default:
        break;
	}
}

void keyboardUp(unsigned char key, int x, int y) {
	//cout << "keyUp " << (int)key << endl;
    Input::sharedInput()->inputUp(key);
    updateModifiers();

	switch (key) {
	case 27: //ESC
		GLContext::destroy();
		break;
	default:
		break;
	}
}

void mouseMoveActive(int x, int y)
{
    Input::sharedInput()->setMouseMovement(x - contextWindowWidth / 2, y - contextWindowHeight / 2);
}

void mouseMovePassive(int x, int y)
{
    Input::sharedInput()->setMouseMovement(x - contextWindowWidth / 2, y - contextWindowHeight / 2);
}

void idle() {
    previousTime = currentTime;
    currentTime = Utility::getSystemTime() - appStartTime;
    GLdouble deltaTime = currentTime - previousTime;

    if (pScene)
    {
        pScene->update(currentTime, deltaTime);
    }

    if (currentTime - fpsLastSecondTime >= 1.0) 
    { //its been a second, so update fps counters
        fpsLastSecondTime += 1.0;

        framesLastSecond = framesThisSecond;
        framesThisSecond = 0;
    }

    glm::ivec2 mouse = Input::sharedInput()->getMouseMovement();
    if (mouse.x != 0 || mouse.y != 0)
    {
        glutWarpPointer(contextWindowWidth / 2, contextWindowHeight / 2);
    }

	glutPostRedisplay();
}

void renderFPS() 
{
    glRasterPos2f(-0.975f, -0.975f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    stringstream stream;
    stream << framesLastSecond << " FPS";

    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) stream.str().c_str());
}

void renderDebugString()
{
    glRasterPos2f(-0.975f, -0.90f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) pScene->getRenderDebugString().c_str());
}

void render() {
	Utility::checkError();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
	if (pScene) 
    {
		pScene->render();

		if (bDrawInfo)
		{
		    glClear(GL_DEPTH_BUFFER_BIT);

			renderFPS();
			renderDebugString();
		}
	}

    framesThisSecond++;

	glutSwapBuffers();
}

void reshape(int width, int height)
{
    contextWindowWidth = width;
    contextWindowHeight = height;
    glViewport(0, 0, width, height);
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
	cout << "GL_SHADERLANG: " << shaderLang << endl << endl;
}

unsigned int GLContext::contextWidth() 
{
	return contextWindowWidth;
}

unsigned int GLContext::contextHeight() 
{
	return contextWindowHeight;
}

void GLContext::setScene(GLScene *scene) 
{
	if (pScene != scene) 
    {
		if (pScene) 
        {
            pScene->release();
			pScene = 0;
		}

        if (scene) 
        {
            pScene = scene;
            pScene->addRef();
        }
	}
}