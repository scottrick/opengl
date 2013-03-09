#pragma once

#include <GL/glew.h>

#ifdef WINDOWS
#include <Windows.h>
#endif

#include <iostream>
using namespace std;

class GLUtility {
public:
	static void checkError() {
		GLenum error = glGetError();
		if (error) {
			cout << "glError: " << error << endl;
		}
	}

    static GLdouble getSystemTime() {
#ifdef WINDOWS
        return (GLdouble)GetTickCount64() / 1000.0;
#endif
    }
};