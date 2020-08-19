#include <GL/glew.h>
#include "renderObjects.h"
#include "Debugger.h"

renderObjects::renderObjects(rect* buffer)
	:renderingRef(buffer)
{
	GLError(glGenVertexArrays(1, &m_vArrayObject));
	GLError(glBindVertexArray(m_vArrayObject));

	GLError(glGenBuffers(1, &m_vBuffer));
	GLError(glBindBuffer(GL_ARRAY_BUFFER, m_vBuffer));
	GLError(glBufferData(GL_ARRAY_BUFFER, renderingRef->getVertArraySize(), renderingRef->rectangleBuffPtr(), GL_STATIC_DRAW));
	/*rectangleBuffPtr returns the refrence of the first index of the recantgle's verticy array. That should be correct*/

	GLError(glEnableVertexAttribArray(0));
	GLError(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL));

	/*We should put a shader object here in some way and be sure that the uniforms are set up properly to use the data from the rectangles color buffer*/
}
renderObjects::~renderObjects()
{
	GLError(glDeleteVertexArrays(1, &m_vArrayObject));
	GLError(glDeleteBuffers(1, &m_vBuffer));
}
void renderObjects::bind()const
{
	GLError(glBindVertexArray(m_vArrayObject));
	/*Whatever shader is being used for the rectangle will need to be bound here too*/
}
void renderObjects::reBuffer(rect* newRectangleBuffer)
{
	renderingRef = newRectangleBuffer;
}
void renderObjects::renderRectangle()const
{
	GLError(glBindBuffer(GL_ARRAY_BUFFER, m_vBuffer));
	GLError(glBufferData(GL_ARRAY_BUFFER, renderingRef->getVertArraySize(), renderingRef->rectangleBuffPtr(), GL_STATIC_DRAW));
}