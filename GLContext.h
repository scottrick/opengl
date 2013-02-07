#pragma once

class GLContext
{
public:
    GLContext();
    ~GLContext();

    void create();
    void destroy();

    void dumpExtensions();
    void dumpInfo();

protected:
	void checkError();

private:

};
