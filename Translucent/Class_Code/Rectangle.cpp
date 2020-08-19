#include "Rectangle.h"

/*A default test rectangle*/
rect::rect(std::string name)
	:m_name(name)
{
	m_color[0] = 1.0f;//Red
	m_color[1] = 1.0f;//Green
	m_color[2] = 1.0f;//Blue
	m_color[3] = 1.0f;//Alpha

	/*x----------------	Value	y------------------ Value*/
	m_rectangleBuff[0].vX = 0.5f; m_rectangleBuff[0].vY = 0.5f;//v0
	m_rectangleBuff[1].vX = 0.5f; m_rectangleBuff[1].vY = -0.5f;//v1
	m_rectangleBuff[2].vX = -0.5f; m_rectangleBuff[2].vY = -0.5f;//v2
	m_rectangleBuff[3].vX = -0.5f; m_rectangleBuff[3].vY = 0.5f;//v3
}
rect::rect(std::string name, vertex* vBuff)
	:m_name(name)
{
	/*I might need a way to error out if I generate 2 rectangles with the same name*/
	m_color[0] = 1.0f;
	m_color[1] = 1.0f;
	m_color[2] = 1.0f;
	m_color[3] = 1.0f;

	/*For loop that sets all the vertices where i is the vertex number. The pointer is meant to be a user generated buffer*/
	for (int i = 0; i < sizeof(m_rectangleBuff) / sizeof(vertex); i++)
	{
		m_rectangleBuff[i].vX = (vBuff + i)->vX; m_rectangleBuff[i].vY = (vBuff + i)->vY;
	}
}

/*Pointer Methods*/
vertex* rect::rectangleBuffPtr() { return &m_rectangleBuff[0]; }
float* rect::colorPtr() { return &m_color[0]; }
void rect::displayData()const
{
	std::cout << "Displaying " << m_name << std::endl << std::endl;
	std::cout << "Vertex Positions" << std::endl;
	for (int i = 0; i < sizeof(m_rectangleBuff) / sizeof(vertex); i++)
	{
		std::cout << "Vertex " << i + 1 << ": (" << m_rectangleBuff[i].vX << ", " << m_rectangleBuff[i].vY << ")" << std::endl;/*Exception error is thrown here. It was a read access violation*/
	}

	const std::string colorValueTypes[] = { "RED", "GREEN", "BLUE", "ALPHA" };

	std::cout << std::endl << "Color Value" << std::endl;
	for (int i = 0; i < sizeof(m_color) / sizeof(float); i++)
		std::cout << colorValueTypes[i] << ": " << m_color[i] << std::endl;
}
unsigned int rect::getVertArraySize()const
{
	return sizeof(m_rectangleBuff);
}