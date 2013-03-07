#include "GLScene.h"

#include <GL/glew.h>
#include <algorithm>

#include "GLRenderable.h"

GLScene::GLScene()
{

}

GLScene::~GLScene()
{
    removeAllRenderables();
}

void GLScene::addRenderable(GLRenderable *pRenderable)
{
    vector<GLRenderable *>::iterator result = std::find(renderables.begin(), renderables.end(), pRenderable);
    if (result == renderables.end()) 
    { //not contained, so add it!
        pRenderable->addRef();
        renderables.push_back(pRenderable);
    }
    else 
    { //already in our list...

    }
}

void GLScene::removeRenderable(GLRenderable *pRenderable)
{
    vector<GLRenderable *>::iterator result = std::find(renderables.begin(), renderables.end(), pRenderable);
    if (result == renderables.end()) 
    { //not contained in our list, so do nothing!

    }
    else 
    { //in our list, so remove it
        renderables.erase(result);
        pRenderable->release();
    }
}
    
void GLScene::removeAllRenderables()
{
    vector<GLRenderable *>::iterator iter;
    for (iter = renderables.begin(); iter != renderables.end(); iter++) 
    {
        GLRenderable *pRenderable = *iter;
        pRenderable->release();
    }

    renderables.clear();
}
