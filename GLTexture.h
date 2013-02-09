#pragma once

#include <GL/glew.h>

class GLTexture
{
public:
	GLTexture(int width, int height, unsigned char *data, bool mipmap);
	~GLTexture();

	GLuint getTexture() const;
	
private:
	GLuint texture;
};

