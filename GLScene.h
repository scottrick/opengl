#pragma once

class GLScene
{
public:
    GLScene();
    ~GLScene();

	virtual void create() = 0;
	virtual void destroy() = 0;

	virtual void prepareRender() = 0;
    virtual void render() = 0;

protected:


private:

};
