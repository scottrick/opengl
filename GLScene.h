#pragma once

#include "../scottbase/Unknown.h"

class GLScene : public Unknown
{
public:
    GLScene();

	virtual void create() = 0;
	virtual void destroy() = 0;

	virtual void prepareRender() = 0;
    virtual void render() = 0;

protected:
    ~GLScene();

private:

};
