#pragma once

class GLTexture;

class GLTextureFactory
{
public:
	static GLTexture *createTextureForPNG(const char *filename);

private:
	GLTextureFactory(void);
	~GLTextureFactory(void);

};

