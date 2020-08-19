#pragma once
#include "Rectangle.h"

class renderObjects
{
private:
	unsigned int m_vBuffer;
	unsigned int m_vArrayObject;
	rect* renderingRef;

public:
	renderObjects(rect* buffer);
	~renderObjects();

	void bind()const;
	void reBuffer(rect* newRectangleBuffer);
	void renderRectangle()const;
};