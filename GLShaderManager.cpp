#include "GLShaderManager.h"

#include "GLShader.h"

GLShaderManager::GLShaderManager()
{

}

GLShaderManager::~GLShaderManager()
{

}

GLShaderManager *GLShaderManager::Manager() 
{
    static GLShaderManager manager;
    return &manager;
}

GLuint GLShaderManager::getShaderProgram(string filename) 
{
    map<string, GLuint>::iterator programIter = programMap.find(filename);
    GLuint shaderProgram;

    if (programIter == programMap.end()) //program not created!  so create it
    { 
        //get the vertex shader
        string vertFilename = filename + ".vert";
        GLShader *vertShader = new GLShader(vertFilename);

        //get the fragment shader
        string fragFilename = filename + ".frag";
        GLShader *fragShader =  new GLShader(fragFilename);
           
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertShader->getShader());
        glAttachShader(shaderProgram, fragShader->getShader());
        glLinkProgram(shaderProgram);

        programMap[filename] = shaderProgram;
    }
    else //program already created
    {
        shaderProgram = programIter->second;
    }

    return shaderProgram;
}