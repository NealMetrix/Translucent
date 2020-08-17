#pragma once
#include <iostream>
#include <vector>

#include "Rectangle.h"

#define invalidString -1
#define bindRectangleC 0
#define colorC 1
#define createRectangleC 2
#define displayC 3
#define generateC 4
#define helpC 5
#define quitC 6

const std::string commandArray[7] = { "bindrectangle","color","createrectangle","display","generate","help","quit" };

struct user
{
private:
	rect* rectPtr;/*Maybe this should be an array or vector of rectangles instead... Actually Yes lets do that*/

public:
	user();

	int input(std::string &inValue);/*Input is supposed to take a string and check if it represents a command*/
	rect* createRectangle();/*How does the user interact with this function??Create a argument that takes a userObject of course.
							Honestly we should take this out of main.cpp and put it as a user method*/

private:
	void color();
	void bindRectangle();
};