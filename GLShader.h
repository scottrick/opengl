#pragma once

#include <string>
#include <GL/glew.h>

#include "../scottbase/Unknown.h"

class GLShader : public Unknown
{
public:
	GLShader(std::string filename);
	~GLShader(void);

	GLuint getShader() const;

protected:
	void compile(std::string filename);

private:
	GLuint shader;

};

