#include "Rectangle.h"
#include <GL/glew.h>

/*A default test rectangle*/
rect::rect()
{
	color[0] = 1.0f;//Red
	color[1] = 1.0f;//Green
	color[2] = 1.0f;//Blue
	color[3] = 1.0f;//Alpha

	/*x----------------	Value	y------------------ Value*/
	rectangleBuff[0].vX = 0.5f; rectangleBuff[0].vY = 0.5f;//v0
	rectangleBuff[1].vX = 0.5f; rectangleBuff[1].vY = -0.5f;//v1
	rectangleBuff[2].vX = -0.5f; rectangleBuff[2].vY = -0.5f;//v2
	rectangleBuff[3].vX = -0.5f; rectangleBuff[3].vY = 0.5f;//v3

	/*Setting Up GL for a specific rectangle*/
	glGenVertexArrays(1, &vArrayObject);
	glBindVertexArray(vArrayObject);

	glGenBuffers(1,&m_VertexID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexID);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vertex), rectangleBuff, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);

	/*I will also want to create a shader object in here to instantiate the shader as a property
	of this class. This way changing the shader would be like changing the color of a specific rectangle*/
}
rect::~rect()
{
	glDeleteVertexArrays(1, &vArrayObject);
	glDeleteBuffers(1, &m_VertexID);
}
/*Pointer Methods*/
vertex* rect::rectangleBuffPtr() { return &rectangleBuff[0]; }
float* rect::colorPtr() { return &color[0]; }

void rect::bindRect()const
{
	glBindVertexArray(vArrayObject);
}