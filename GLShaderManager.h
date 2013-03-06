#pragma once

#include <GL/glew.h>

#include <string>
#include <map>
using namespace std;

class GLShader;

class GLShaderManager
{
public:
    static GLShaderManager *Manager();

    GLuint getShaderProgram(string filename); //pass "ColoredGeometry" and it will build the program from the corresponding .vert and .frag files

private:
    GLShaderManager();
    ~GLShaderManager();

    map<string, GLuint> programMap;
};

