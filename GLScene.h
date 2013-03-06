#pragma once

#include "../scottbase/Unknown.h"

class GLScene : public Unknown
{
public:
    GLScene();

    virtual void render() = 0;

protected:
    ~GLScene();

private:

};
