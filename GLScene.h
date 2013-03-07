#pragma once

#include "../scottbase/Unknown.h"

#include <vector>
using namespace std;

class GLRenderable;

class GLScene : public Unknown
{
public:
    GLScene();

    virtual void render() = 0;

    void addRenderable(GLRenderable *pRenderable);
    void removeRenderable(GLRenderable *pRenderable);
    
    void removeAllRenderables();

protected:
    ~GLScene();

    vector<GLRenderable *> renderables;

private:

};
