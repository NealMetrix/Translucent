#pragma once
#include <fstream>
#include <string>
#include <sstream>

#include "Rectangle.h"

enum class shaderType
{
	NONE=0, VERTEX = 1, FRAGMENT = 2
};
struct shaderSource
{
	std::string vertex;
	std::string fragment;
};
class colors
{
private:
	unsigned int m_shaderID;/*I am not sure if this should be public or private because I might want to Be able to pair select different shaders with different quadralaterals*/
	std::string m_filePath;
	shaderSource fullCode;
	rect* watcher;

public:
	colors(std::string filepath, rect* watchedObject);
	~colors();
	void bind()const;
	void unbind()const;
	void rewatch(rect* changedRectangle);
	void setUniform()const;
private:
	shaderSource parse(std::string& filepath)const;
};