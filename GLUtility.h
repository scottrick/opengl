#pragma once

#include <GL/glew.h>

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
};