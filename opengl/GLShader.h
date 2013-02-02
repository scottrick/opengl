#pragma once

#include <string>
#include <GL/glew.h>

class GLShader
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

