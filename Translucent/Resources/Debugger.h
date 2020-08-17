#pragma once
#include<GL/glew.h>
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