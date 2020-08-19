#include <fstream>
#include <string>

#include "Debugger.h"
#include "color.h"

colors::colors(std::string filepath, rect* watchedObject)
	:m_filePath(filepath), watcher(watchedObject)
{
	shaderSource filesourceCode = parse(m_filePath);

	const char* vertexSource = filesourceCode.vertex.c_str();
	const char* fragmentSource = filesourceCode.fragment.c_str();
	/*Cherno probably doesn't do this because of speed. You would be parsing the code 2x instead of doing it once and
	setting it equal to the struct values. Sure one you are sacrificing memory and the other you are sacrificing speed
	but the bigger your shader sourcecode is the more that the speed starts to outweigh the memory. Just figured I'd try
	it this way to see if it works*/

	GLError(m_shaderID = glCreateProgram());

	GLError(unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER));
	GLError(unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));

	GLError(glShaderSource(vertexShader, 1, &vertexSource, NULL));
	GLError(glShaderSource(fragmentShader, 1, &fragmentSource, NULL));

	GLError(glCompileShader(vertexShader));
	GLError(glCompileShader(fragmentShader));

	GLError(glAttachShader(m_shaderID, vertexShader));
	GLError(glAttachShader(m_shaderID, fragmentShader));

	GLError(glDeleteShader(vertexShader));
	GLError(glDeleteShader(fragmentShader));

	GLError(glLinkProgram(m_shaderID));
	GLError(glValidateProgram(m_shaderID));

	GLError(glUseProgram(m_shaderID));/*shader becomes used/bound by default*/
}
shaderSource colors::parse(std::string& filepath)const
{
	std::ifstream codeLocation(filepath);
	std::stringstream graphicsCode[2];
	std::string line;
	shaderType sType = shaderType::NONE;
	while (getline(codeLocation, line))
	{
		if (line.find("#Shader") != std::string::npos)
		{
			if (line.find("Vertex") != std::string::npos)
				sType = shaderType::VERTEX;

			else if (line.find("Fragment") != std::string::npos)
				sType = shaderType::FRAGMENT;

			else
				std::cout << "WARNING: Undefined shader type, shader type remains unchanged" << std::endl;
		}
		else
		{
			std::cout << line << std::endl;

			if ((int)sType != 0)
				graphicsCode[(int)sType - 1] << line << std::endl;
			else
				std::cout << "ERROR: Fragment type is null. Strings have been lost" << std::endl;
		}
	}
	return { graphicsCode[0].str(), graphicsCode[1].str() };
}
colors::~colors()
{
	GLError(glDeleteProgram(m_shaderID));
}
void colors::bind()const
{
	GLError(glUseProgram(m_shaderID));
}
void colors::unbind()const
{
	GLError(glUseProgram(0));
}
void colors::rewatch(rect* changedRectangle)
{
	watcher = changedRectangle;
}
void colors::setUniform()const
{
	/*Function will set the data the uniform gets*/

	GLError(glUniform4f(glGetUniformLocation(m_shaderID, "userColorUniform"), *(watcher->colorPtr() + 0), *(watcher->colorPtr() + 1), *(watcher->colorPtr() + 2), *(watcher->colorPtr() + 3)));
}