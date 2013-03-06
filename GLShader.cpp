#include "GLShader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

GLShader::GLShader(std::string filename) {
	compile(filename);
}

GLShader::~GLShader() {
	glDeleteShader(shader);
}

void GLShader::compile(std::string filename) {
	//read the file
	std::fstream shaderFile(filename);
	std::stringstream buffer;
	buffer << shaderFile.rdbuf();
	std::string shaderText = std::string(buffer.str());

	//determine if this is a vert or frag shader
	if (filename.find(".vert") != std::string::npos) {
		shader = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (filename.find(".frag") != std::string::npos) {
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else {
		assert(0 && "invalid shader filename");
	}

	//compile the shader
	const char *text = shaderText.c_str();
	glShaderSource(shader, 1, &text, NULL);
	glCompileShader(shader);

	//check for errors
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status); 

	if (status) {
		std::cout << filename << " compiled successfully.\n";
	}
	else { 
		//error compiling shader
		char buffer[1024];
		glGetShaderInfoLog(shader, 1024, NULL, buffer);
		std::cout << "ERROR compiling \"" << filename << "\":" << std::endl << buffer << std::endl;
	}
}

GLuint GLShader::getShader() const {
	return shader;
}

const char *GLShader::GetClassName() const {
    return "GLShader"; 
}