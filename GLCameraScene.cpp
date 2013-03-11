#include "GLCameraScene.h"

#include "GLCamera.h"
#include "GLColoredGeometry.h"
#include "GLContext.h"
#include "GLRenderable.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

GLCameraScene::GLCameraScene() 
    : pCamera(0)
{
    GLCamera *camera = new GLCamera();
    setCamera(camera);
    camera->release();

    for (GLfloat z = -40.0f; z < 40.0f; z += 6.5f) 
    {
        for (GLfloat x = -40.0f; x < 40.0f; x += 6.5f)
        {
            GLfloat vertices[] = {
	        -0.5f + x, -0.5f, 0.5f + z, 1.0f, 0.0f, 0.0f, //x, y, z, r, g, b
	        0.5f + x, -0.5f, 0.5f + z, 0.0f, 1.0f, 0.0f, 
	        0.5f + x,  0.5f, 0.5f + z, 0.0f, 0.0f, 1.0f, 
	        -0.5f + x,  0.5f, 0.5f + z, 1.0f, 1.0f, 0.0f, 
	        -0.5f + x, -0.5f, -0.5f + z, 0.0f, 1.0f, 1.0f,
	        0.5f + x, -0.5f, -0.5f + z, 1.0f, 0.0f, 1.0f, 
	        0.5f + x,  0.5f, -0.5f + z, 1.0f, 1.0f, 1.0f, 
	        -0.5f + x,  0.5f, -0.5f + z, 0.0f, 0.0f, 0.0f, 
            };

            GLuint elements[] = {
                0, 1, 2, //front
                0, 2, 3,
                1, 5, 6, //right
                1, 6, 2,
                5, 4, 7, //back
                5, 7, 6,
                4, 0, 3, //left
                4, 3, 7,
                3, 2, 6, //top
                3, 6, 7,
                4, 5, 1, //bottom 
                4, 1, 0,
            };

            GLRenderable *pRenderable = new GLColoredGeometry(vertices, 8, elements, 36);
            addRenderable(pRenderable);
            pRenderable->release();
        }
    }
}

GLCameraScene::~GLCameraScene() 
{
    setCamera(0);
}

void GLCameraScene::render() 
{
    GLuint currentShaderProgram = -1;
    vector<GLRenderable *>::iterator iter;

    for (iter = renderables.begin(); iter != renderables.end(); iter++)
    { //render everything!
        GLRenderable *pRenderable = *iter;
        
        if (currentShaderProgram != pRenderable->getShaderProgram())
        { //new shader for this renderable, so set it up!
            currentShaderProgram = pRenderable->getShaderProgram();

            glUseProgram(currentShaderProgram);
	        GLuint viewTransformUniform = glGetUniformLocation(currentShaderProgram, "view");
	        GLuint projTransformUniform = glGetUniformLocation(currentShaderProgram, "proj");

            //setup the camera
            glm::mat4 proj = glm::perspective(pCamera->fov, (float)GLContext::contextWidth() / (float)GLContext::contextHeight(), 1.0f, 200.0f);
            glUniformMatrix4fv(projTransformUniform, 1, GL_FALSE, glm::value_ptr(proj));

            glm::mat4 view = glm::lookAt(
                pCamera->pos,
                pCamera->pos + pCamera->lookDir,
                pCamera->upDir
            );
            glUniformMatrix4fv(viewTransformUniform, 1, GL_FALSE, glm::value_ptr(view));
        }

        pRenderable->render();
    }
}

void GLCameraScene::update(GLdouble time, GLdouble deltaTime)
{
    if (pCamera) 
    {
        pCamera->update(time, deltaTime);
    }
}

const char *GLCameraScene::getClassName() const 
{ 
    return "GLCameraScene";
}

void GLCameraScene::setCamera(GLCamera *camera) 
{
    if (pCamera != camera)
    {
        if (pCamera)
        {
            pCamera->release();
            pCamera = 0;
        }

        if (camera) 
        {
            pCamera = camera;
            pCamera->addRef();
        }
    }
}