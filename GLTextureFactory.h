#pragma once

class GLTexture;

class GLTextureFactory
{
public:
    static GLTexture *createTextureForImage(const char *imageFilename);

private:
    GLTextureFactory(void);
    ~GLTextureFactory(void);
};
