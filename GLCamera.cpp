#include "GLCamera.h"

#include "Input.h"

GLCamera::GLCamera()
{
    fov = 45.0f;
    
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
    lookDir = glm::vec3(0.0f, 0.0f, 1.0f);
    upDir = glm::vec3(0.0f, 1.0f, 0.0f);

    speed = 10.0f;
}

GLCamera::~GLCamera()
{

}

void GLCamera::update(GLdouble time, GLdouble deltaTime)
{
    GLulong input = Input::sharedInput()->getKeyboardAlphaFlags();
    GLulong modifiers = Input::sharedInput()->getKeyboardModifierFlags();
    
    if (input & INPUT_CHAR_W) 
    { //moving forwards
        pos += lookDir * (speed * (GLfloat)deltaTime);
    }

    if (input & INPUT_CHAR_S) 
    { //moving backwards
        pos -= lookDir * (speed * (GLfloat)deltaTime);
    }

    if (input & INPUT_CHAR_A)
    { //moving left
        glm::vec3 cross = glm::cross(lookDir, upDir);
        pos -= cross * (speed * (GLfloat)deltaTime);
    }

    if (input & INPUT_CHAR_D)
    { //moving right
        glm::vec3 cross = glm::cross(lookDir, upDir);
        pos += cross * (speed * (GLfloat)deltaTime);
    }

    if (input & INPUT_SPACE)
    { 
        if (modifiers & INPUT_MODIFIER_SHIFT)
        { //moving down
            pos -= upDir * (speed * (GLfloat)deltaTime);
        }
        else
        { //moving up
            pos += upDir * (speed * (GLfloat)deltaTime);
        }
    }
}

const char *GLCamera::getClassName() const 
{
    return "GLCamera";
}
