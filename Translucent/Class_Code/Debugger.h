#pragma once
#include<GL/glew.h>
#include<iostream>

#define ASSERT(x) if(!(x)) __debugbreak()
#define GLError(x) GLClearError(); x; ASSERT(GLErrorLog(#x,__FILE__,__LINE__))
/*Make debugging code for openGL we need it again.*/

/*Remember to make sure that these definitions are static
If you don't you could have a lot of linker errors when you build your code*/
static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR){}
}

static bool GLErrorLog(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "OpenGL ERROR: (" << error << ") " << function << " in -> " << file << " on: " << line << std::endl;
		return false;
	}
	return true;
}

/*Originally built for checking the increment value of a void ptr
However I learned from this that T does not have a defined size so
it will just create an error*/
template <typename T>
T incrementchecker(T &value)
{
	T store = value;
	value++;
	return value - store;
}