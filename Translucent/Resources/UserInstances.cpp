#include "UserInstances.h"
user::user():rectPtr(0){}/*Starts by pointing to nothing*/

int user::input(std::string &inValue)
{
	int i;
	for (i = colorC; i <= quitC && inValue!=commandArray[i]; i++){}/*Loop where i value will be set to the index of the command array*/

	switch (i)
	{
	case bindRectangleC:
		break;
	case colorC:
		color();
		return colorC;
	case createRectangleC:
		createRectangle();
		return createRectangleC;
	case displayC:
		return displayC;
	case generateC:
		return generateC;
	case helpC:
		return helpC;
	case quitC:
		return quitC;
	default:
		return invalidString;
	}
}
void user::bindRectangle()
{
	/*I could just cast the rectPtr to a vertex pointer but this way is safer because even if we accidently switch the order between*/
	vertex* rectangleVertexPtr = rectPtr->rectangleBuffPtr();

	float userValue;
	for (int i = 0; i < 4; i++)
	{
		userValue = 0.0f;

		std::cout << "Input an X value for the Vertex" << std::endl;
		std::cin >> userValue;
		(rectangleVertexPtr + i)->vX = userValue;

		std::cout << "Input a Y value for the Vertex" << std::endl;
		std::cin >> userValue;
		(rectangleVertexPtr + i)->vY = userValue;
	}
}
void user::color()
{
	float* rectColorPtr = rectPtr->colorPtr();
	float userValue;
	std::string colorBuffNames[] = { "RED", "GREEN", "BLUE", "ALPHA" };
	for (int i = 0; i < 4; i++)
	{
		userValue = 0.0f;

		std::cout << "Input " << colorBuffNames[i] << " value" << std::endl;
		std::cin >> (*(rectColorPtr + i));
	}
}
rect* user::createRectangle()
{
	char yN;
	/*Needs to be able to specify values for the rectangle*/
	std::cout << "Specify Coorinates?\nIf no default coordinates will be set.\nType y/n: " << std::endl;
	std::cin >> yN;
	if (yN == 'y')
	{
		/*Creates a vertex buffer to give to a new rect object so it can instantiate it*/
	}
	else if(yN == 'n')
	{
		rect* defaultRectangle = new rect();
		return defaultRectangle;
	}
	else
	{
		std::cout << "ERROR: Invalid Input" << std::endl;
		return NULL;
	}
}