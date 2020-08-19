#pragma once
#include<iostream>
struct vertex
{
	float vX;
	float vY;

	void logCoordinate()
	{
		std::cout << "(" << vX << ", " << vY << ")" << std::endl;
	}
};
/*I only want this class to be accessed through user input. Lets just have functions that return pointers*/
class rect
{
public:
	std::string m_name;

private:
	/*Properties*/
	vertex m_rectangleBuff[4];
	float m_color[4];

public:
	/*Constructors/Destructors*/
	rect(std::string name);
	rect(std::string name, vertex* vBuff);

	/*Pointer Methods*/
	vertex* rectangleBuffPtr();
	float* colorPtr();
	unsigned int getVertArraySize()const;

	void displayData()const;
};