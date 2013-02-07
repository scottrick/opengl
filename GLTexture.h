#pragma once

#include <GL/glew.h>

class GLTexture
{
public:
	GLTexture(GLuint texture);
	~GLTexture();

private:
	GLuint texture;
};

