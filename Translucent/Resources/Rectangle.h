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
	/*Properties*/
	unsigned int vArrayObject;
	unsigned int m_VertexID;
	vertex rectangleBuff[4];
	float color[4];

public:
	/*Constructors/Destructors*/
	rect();
	~rect();

	/*Pointer Methods*/
	vertex* rectangleBuffPtr();
	float* colorPtr();

	void bindRect()const;
};