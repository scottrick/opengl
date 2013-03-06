#pragma once

#include <string>
#include <GL/glew.h>

#include "../scottbase/Unknown.h"

class GLShader : public Unknown
{
public:
	GLShader(std::string filename);

	GLuint getShader() const;

    const char *GetClassName() const;

protected:
	~GLShader();

    void compile(std::string filename);

private:
	GLuint shader;

};

