#pragma once
#include <iostream>
#include <vector>

#include "Rectangle.h"

#define invalidString -1
#define bindC 0
#define clearC 1
#define colorC 2
#define createRectangleC 3
#define deleteC 4
#define displayC 5
#define generateC 6
#define helpC 7
#define listNamesC 8
#define quitC 9
#define repositionC 10

const std::string commandArray[11] = { "bind","clear","color","createrectangle","delete","display","generate","help", "listnames","quit","reposition" };

class user
{
public:
	std::vector<rect*>rectangleRefrenceList;/*Need a way to name the rectangles 1st though*/
private:
	rect* rectPtr;

public:
	user();

	int input(std::string &inValue);/*Input is supposed to take a string and check if it represents a command*/
	rect* createRectangle();/*How does the user interact with this function??Create a argument that takes a userObject of course.
							Honestly we should take this out of main.cpp and put it as a user method*/

private:
	void bindRectangle();
	void color();
	void clear()const;
	void deleteRectangle();
	void display()const;
	void help()const;
	void listNames()const;
	void reposition();
};