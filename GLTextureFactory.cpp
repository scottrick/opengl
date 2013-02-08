#include "GLTextureFactory.h"

#include <SOIL.h>
#include "GLTexture.h"
#include <iostream>
using namespace std;

GLTextureFactory::GLTextureFactory(void)
{

}

GLTextureFactory::~GLTextureFactory(void)
{

}

GLTexture *GLTextureFactory::createTextureForImage(const char *imageFilename)
{
	int width, height;
	unsigned char* image = SOIL_load_image(imageFilename, &width, &height, 0, SOIL_LOAD_RGB);
	
	GLTexture *newTexture = new GLTexture(width, height, image, true);
	SOIL_free_image_data(image);

	return newTexture;
}