#include "GLCamera.h"

#include "Input.h"
#include "glm/gtx/rotate_vector.hpp"
#include <iostream>
using namespace std;

GLCamera::GLCamera()
{
    fov = 60.f;
    
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
    lookDir = glm::vec3(0.0f, 0.0f, 1.0f);
    upDir = glm::vec3(0.0f, 1.0f, 0.0f);

    speed = 100.0f;
}

GLCamera::~GLCamera()
{

}

void GLCamera::update(GLdouble time, GLdouble deltaTime)
{
    GLulong input = Input::sharedInput()->getKeyboardAlphaFlags();
    GLulong modifiers = Input::sharedInput()->getKeyboardModifierFlags();
    glm::ivec2 mouse = Input::sharedInput()->getMouseMovement();

	GLfloat speedToUse = speed;

	if (mouse.x || mouse.y) 
	{
		cout << "Mouse (" << mouse.x << ", " << mouse.y << ")" << endl;
		cout << "LookDir (" << lookDir.x << ", " << lookDir.y << ", " << lookDir.z << ")" << endl;

		if (mouse.x)
		{
			lookDir = glm::rotate(lookDir, -0.2f * (GLfloat)mouse.x, upDir);
		}

		if (mouse.y)
		{
			glm::vec3 crossVec = glm::cross(lookDir, upDir);
			lookDir = glm::rotate(lookDir, -0.2f * (GLfloat)mouse.y, crossVec);
			upDir = glm::rotate(upDir, -0.2f * (GLfloat)mouse.y, crossVec);
		}

		cout << "LookDir (" << lookDir.x << ", " << lookDir.y << ", " << lookDir.z << ")" << endl;
	}

	if (modifiers & INPUT_MODIFIER_ALT) 
	{
		speedToUse /= 12.0f;
	}

	if (input & INPUT_CHAR_W) 
    { //moving forwards
        pos += lookDir * (speedToUse * (GLfloat)deltaTime);
    }

    if (input & INPUT_CHAR_S) 
    { //moving backwards
        pos -= lookDir * (speedToUse * (GLfloat)deltaTime);
    }

    if (input & INPUT_CHAR_A)
    { //moving left
        glm::vec3 cross = glm::cross(lookDir, upDir);
        pos -= cross * (speedToUse * (GLfloat)deltaTime);
    }

    if (input & INPUT_CHAR_D)
    { //moving right
        glm::vec3 cross = glm::cross(lookDir, upDir);
        pos += cross * (speedToUse * (GLfloat)deltaTime);
    }

    if (input & INPUT_SPACE)
    { 
        if (modifiers & INPUT_MODIFIER_SHIFT)
        { //moving down
            pos -= upDir * (speedToUse * (GLfloat)deltaTime);
        }
        else
        { //moving up
            pos += upDir * (speedToUse * (GLfloat)deltaTime);
        }
    }
}

const char *GLCamera::getClassName() const 
{
    return "GLCamera";
}
