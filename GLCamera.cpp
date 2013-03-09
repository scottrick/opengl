#include "GLCamera.h"

#include "Input.h"
#include "glm/gtc/matrix_transform.hpp"

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
    glm::ivec2 mouse = Input::sharedInput()->getMouseMovement();
    
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

    if (mouse.x)
    {
        //glm::mat2x3 rotationAroundY = glm::mat3x3(
        //glm::mat4 rotation = glm::mat3
    }

    if (mouse.y)
    {

    }
}

const char *GLCamera::getClassName() const 
{
    return "GLCamera";
}
