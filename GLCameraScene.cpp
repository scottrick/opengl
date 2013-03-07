#include "GLCameraScene.h"

#include "GLCamera.h"
#include "GLColoredGeometry.h"
#include "GLContext.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

GLCameraScene::GLCameraScene() 
    : pCamera(0)
{
    GLCamera *camera = new GLCamera();
    setCamera(camera);
    camera->Release();

    GLfloat vertices[] = {
	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, //x, y, z, r, g, b
	0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 
	0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 
	-0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 
	-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 
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

    pRenderable = new GLColoredGeometry(vertices, 8, elements, 36);
}

GLCameraScene::~GLCameraScene() 
{
    setCamera(0);
    pRenderable->Release();
}

void GLCameraScene::render() 
{
    GLuint shaderProgram = pRenderable->getShaderProgram();
    glUseProgram(shaderProgram);

	GLuint viewTransformUniform = glGetUniformLocation(shaderProgram, "view");
	GLuint projTransformUniform = glGetUniformLocation(shaderProgram, "proj");

    //setup the camera
    glm::mat4 proj = glm::perspective(pCamera->fov, (float)GLContext::contextWidth() / (float)GLContext::contextHeight(), 1.0f, 10.0f);
    glUniformMatrix4fv(projTransformUniform, 1, GL_FALSE, glm::value_ptr(proj));

    glm::mat4 view = glm::lookAt(
        glm::vec3(pCamera->cameraX, pCamera->cameraY, pCamera->cameraZ),
        glm::vec3(pCamera->lookAtX, pCamera->lookAtY, pCamera->lookAtZ),
        glm::vec3(pCamera->upDirX, pCamera->upDirY, pCamera->upDirZ)
    );
    glUniformMatrix4fv(viewTransformUniform, 1, GL_FALSE, glm::value_ptr(view));

    pRenderable->render();
}

const char *GLCameraScene::GetClassName() const 
{ 
    return "GLCameraScene";
}

void GLCameraScene::setCamera(GLCamera *camera) 
{
    if (pCamera != camera)
    {
        if (pCamera)
        {
            pCamera->Release();
            pCamera = 0;
        }

        if (camera) 
        {
            pCamera = camera;
            pCamera->AddRef();
        }
    }
}