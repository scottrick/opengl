#include "GLTexture.h"

GLTexture::GLTexture(GLuint texture)
{
	this->texture = texture;
}

GLTexture::~GLTexture(void)
{
	glDeleteTextures(1, &texture);
}
