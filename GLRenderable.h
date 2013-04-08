#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "..\scottbase\unknown.h"
#include <GL/glew.h>

class GLRenderable : public Unknown
{
public:
    GLRenderable();

    virtual void render() const = 0;
    virtual GLuint getShaderProgram() const = 0;

	virtual const glm::mat4 &getModelMatrix() const = 0;
	virtual GLuint getTriangleCount() const = 0;

protected:
    ~GLRenderable();

};

