#pragma once
#include <iostream>
#include <vector>

#include "Rectangle.h"

#define invalidString -1
#define colorC 0
#define createRectangleC 1
#define displayC 2
#define generateC 3
#define helpC 4
#define quitC 5

const std::string commandArray[6] = { "color","createrectangle","display","generate","help","quit" };

struct user
{
private:
	rect* rectPtr;/*Maybe this should be an array or vector of rectangles instead... Actually Yes lets do that*/
	std::vector<rect> userRectangles[];
	/*If this class has the vector of rectangles then we will have to have a method for user that binds different buffers rectangles with
	different drawcalls.*/
public:
	user(rect* ptr);

	int input(std::string &inValue);/*Input is supposed to take a string and check if it represents a command*/

private:
	void color();
	void createRectangle();
};