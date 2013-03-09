#include "Input.h"

Input *Input::sharedInput()
{
	static Input theInput;
	return &theInput;
}

Input::Input()
{
    alphaFlags = 0;
    modifierFlags = 0;
}

Input::~Input()
{

}

void Input::inputDown(unsigned char key)
{
	switch (key)
	{
	case 'a':
	case 'A':
		raiseAlphaFlags(INPUT_CHAR_A);
		break;
	case 'b':
	case 'B':
		raiseAlphaFlags(INPUT_CHAR_B);
		break;
	case 'c':
	case 'C':
		raiseAlphaFlags(INPUT_CHAR_C);
		break;
	case 'd':
	case 'D':
		raiseAlphaFlags(INPUT_CHAR_D);
		break;
	case 'e':
	case 'E':
		raiseAlphaFlags(INPUT_CHAR_E);
		break;
	case 'f':
	case 'F':
		raiseAlphaFlags(INPUT_CHAR_F);
		break;
	case 'g':
	case 'G':
		raiseAlphaFlags(INPUT_CHAR_G);
		break;
	case 'h':
	case 'H':
		raiseAlphaFlags(INPUT_CHAR_H);
		break;
	case 'i':
	case 'I':
		raiseAlphaFlags(INPUT_CHAR_I);
		break;
	case 'j':
	case 'J':
		raiseAlphaFlags(INPUT_CHAR_J);
		break;
	case 'k':
	case 'K':
		raiseAlphaFlags(INPUT_CHAR_K);
		break;
	case 'l':
	case 'L':
		raiseAlphaFlags(INPUT_CHAR_L);
		break;
	case 'm':
	case 'M':
		raiseAlphaFlags(INPUT_CHAR_M);
		break;
	case 'n':
	case 'N':
		raiseAlphaFlags(INPUT_CHAR_N);
		break;
	case 'o':
	case 'O':
		raiseAlphaFlags(INPUT_CHAR_O);
		break;
	case 'p':
	case 'P':
		raiseAlphaFlags(INPUT_CHAR_P);
		break;
	case 'q':
	case 'Q':
		raiseAlphaFlags(INPUT_CHAR_Q);
		break;
	case 'r':
	case 'R':
		raiseAlphaFlags(INPUT_CHAR_R);
		break;
	case 'S':
	case 's':
		raiseAlphaFlags(INPUT_CHAR_S);
		break;
	case 't':
	case 'T':
		raiseAlphaFlags(INPUT_CHAR_T);
		break;
	case 'u':
	case 'U':
		raiseAlphaFlags(INPUT_CHAR_U);
		break;
	case 'v':
	case 'V':
		raiseAlphaFlags(INPUT_CHAR_V);
		break;
	case 'w':
	case 'W':
		raiseAlphaFlags(INPUT_CHAR_W);
		break;
	case 'x':
	case 'X':
		raiseAlphaFlags(INPUT_CHAR_X);
		break;
	case 'y':
	case 'Y':
		raiseAlphaFlags(INPUT_CHAR_Y);
		break;
	case 'z':
	case 'Z':
		raiseAlphaFlags(INPUT_CHAR_Z);
		break;
	case ' ':
		raiseAlphaFlags(INPUT_SPACE);
		break;

	default:
		break;
	}
}

void Input::inputUp(unsigned char key)
{
	switch (key)
	{
	case 'a':
	case 'A':
		lowerAlphaFlags(INPUT_CHAR_A);
		break;
	case 'b':
	case 'B':
		lowerAlphaFlags(INPUT_CHAR_B);
		break;
	case 'c':
	case 'C':
		lowerAlphaFlags(INPUT_CHAR_C);
		break;
	case 'd':
	case 'D':
		lowerAlphaFlags(INPUT_CHAR_D);
		break;
	case 'e':
	case 'E':
		lowerAlphaFlags(INPUT_CHAR_E);
		break;
	case 'f':
	case 'F':
		lowerAlphaFlags(INPUT_CHAR_F);
		break;
	case 'g':
	case 'G':
		lowerAlphaFlags(INPUT_CHAR_G);
		break;
	case 'h':
	case 'H':
		lowerAlphaFlags(INPUT_CHAR_H);
		break;
	case 'i':
	case 'I':
		lowerAlphaFlags(INPUT_CHAR_I);
		break;
	case 'j':
	case 'J':
		lowerAlphaFlags(INPUT_CHAR_J);
		break;
	case 'k':
	case 'K':
		lowerAlphaFlags(INPUT_CHAR_K);
		break;
	case 'l':
	case 'L':
		lowerAlphaFlags(INPUT_CHAR_L);
		break;
	case 'm':
	case 'M':
		lowerAlphaFlags(INPUT_CHAR_M);
		break;
	case 'n':
	case 'N':
		lowerAlphaFlags(INPUT_CHAR_N);
		break;
	case 'o':
	case 'O':
		lowerAlphaFlags(INPUT_CHAR_O);
		break;
	case 'p':
	case 'P':
		lowerAlphaFlags(INPUT_CHAR_P);
		break;
	case 'q':
	case 'Q':
		lowerAlphaFlags(INPUT_CHAR_Q);
		break;
	case 'r':
	case 'R':
		lowerAlphaFlags(INPUT_CHAR_R);
		break;
	case 'S':
	case 's':
		lowerAlphaFlags(INPUT_CHAR_S);
		break;
	case 't':
	case 'T':
		lowerAlphaFlags(INPUT_CHAR_T);
		break;
	case 'u':
	case 'U':
		lowerAlphaFlags(INPUT_CHAR_U);
		break;
	case 'v':
	case 'V':
		lowerAlphaFlags(INPUT_CHAR_V);
		break;
	case 'w':
	case 'W':
		lowerAlphaFlags(INPUT_CHAR_W);
		break;
	case 'x':
	case 'X':
		lowerAlphaFlags(INPUT_CHAR_X);
		break;
	case 'y':
	case 'Y':
		lowerAlphaFlags(INPUT_CHAR_Y);
		break;
	case 'z':
	case 'Z':
		lowerAlphaFlags(INPUT_CHAR_Z);
		break;
	case ' ':
		lowerAlphaFlags(INPUT_SPACE);
        break;
    case 27: //esc
        lowerAlphaFlags(INPUT_ESC);
		break;

	default:
		break;
	}	
}

void Input::setModifiers(GLulong modifiers) 
{
    modifierFlags = modifiers;
}

void Input::setMouseMovement(GLint x, GLint y)
{
    mouseMovement.x = x;
    mouseMovement.y = y;
}

const glm::ivec2 Input::getMouseMovement() const
{
    return mouseMovement;
}

void Input::lowerAlphaFlags(GLulong dwFlags)
{
	dwFlags = ~dwFlags;
    alphaFlags &= dwFlags;
}

void Input::raiseAlphaFlags(GLulong dwFlags)
{
	alphaFlags |= dwFlags;
}