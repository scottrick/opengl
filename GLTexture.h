#pragma once

#include "../scottbase/Unknown.h"

#include <GL/glew.h>

class GLTexture : public Unknown
{
public:
	GLTexture(int width, int height, unsigned char *data, bool mipmap);

	GLuint getTexture() const;

    //unknown
    const char *getClassName() const;

protected:
   	~GLTexture();

private:
	GLuint texture;
};

