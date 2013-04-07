#include "GLCamera.h"

#include "Input.h"
#include "glm/gtx/rotate_vector.hpp"

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

    if (mouse.x)
    {
        lookDir = glm::rotate(lookDir, -0.2f * (GLfloat)mouse.x, upDir);
    }

    if (mouse.y)
    {
        lookDir = glm::rotate(lookDir, -0.2f * (GLfloat)mouse.y, glm::cross(lookDir, upDir));
    }

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
