#pragma once

#include "../scottbase/Unknown.h"

#include <GL/glew.h>
#include <vector>
#include <string>
using namespace std;

class GLRenderable;

class GLScene : public Unknown
{
public:
    GLScene();

    virtual void render() = 0;
    virtual void update(GLdouble time, GLdouble deltaTime) = 0;
	virtual string getRenderDebugString() const = 0;

    void addRenderable(GLRenderable *pRenderable);
    void removeRenderable(GLRenderable *pRenderable);
    
    void removeAllRenderables();

protected:
    ~GLScene();

    vector<GLRenderable *> renderables;

private:

};
