#include "UserInstances.h"
user::user():rectPtr(0){}/*Starts by pointing to nothing*/

int user::input(std::string &inValue)
{
	int i;
	for (i = colorC; i <= quitC && inValue!=commandArray[i]; i++){}/*Loop where i value will be set to the index of the command array*/

	switch (i)
	{
	case bindRectangleC:
		bindRectangle();
		break;
	case colorC:
		color();
		return colorC;
	case createRectangleC:
		createRectangle();
		return createRectangleC;
	case displayC:
		display();
		return displayC;
	case generateC:
		std::cout << "Generating..." << std::endl;
		return generateC;
	case helpC:
		help();
		return helpC;
	case quitC:
		return quitC;
	default:
		return invalidString;
	}
	return invalidString;
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
		vertex tempVertexBuffer[4];
		for (int i = 0; i < 4; i++)
		{
			/*Maybe create restrictions that force it to be within a -1 and 1 value so it has to be on screen but I won't deal with that at the moment. */
			std::cout << "Input an X value for the Vertex" << std::endl;
			std::cin >> tempVertexBuffer[i].vX;
			std::cout << "Input a Y value for the Vertex" << std::endl;
			std::cin >> tempVertexBuffer[i].vY;
		}
		vertex* tempVertexBufferPtr = &tempVertexBuffer[0];
		rect* defaultRectangle = new rect(tempVertexBufferPtr);

		return defaultRectangle;/*Now that this data is stored on the heap all we need to do is be sure that the is stored in a vector or something.*/
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
void user::display()const
{
	rectPtr->displayData();
}
void user::help()const
{
	std::cout << commandArray[bindRectangleC] << "\		Selects a different rectangle for the other commands to be used on" << std::endl;
	std::cout << commandArray[colorC] << "\		Allows you to specify new color values for your rectangles/quadraleteral" << std::endl;
	std::cout << commandArray[createRectangleC] << "\		Creates a new rectangle and binds it" << std::endl;
	std::cout << commandArray[displayC] << "\		Selects a different rectangle for the other commands to be used on" << std::endl;
	std::cout << commandArray[generateC] << "\		Selects a different rectangle for the other commands to be used on" << std::endl;
	std::cout << commandArray[helpC] << "\		Selects a different rectangle for the other commands to be used on" << std::endl;
	std::cout << commandArray[quitC] << "\		Selects a different rectangle for the other commands to be used on" << std::endl << std::endl;
}