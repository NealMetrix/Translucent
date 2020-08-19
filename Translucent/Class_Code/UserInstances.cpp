#include "UserInstances.h"
#include <stdlib.h>/*I am guessing that this gives you a bunch of operating system and command console commands*/
user::user():rectPtr(0){}/*Starts by pointing to nothing*/

int user::input(std::string &inValue)
{
	int i;
	for (i = bindC; i <= repositionC && inValue!=commandArray[i]; i++){}/*Loop where i value will be set to the index of the command array*/

	switch (i)
	{
	case bindC:
		bindRectangle();
		return bindC;
	case clearC:
		clear();
		return clearC;
	case colorC:
		color();
		return colorC;
	case createRectangleC:
		createRectangle();
		return createRectangleC;
	case deleteC:
		deleteRectangle();
		return deleteC;
	case displayC:
		display();
		return displayC;
	case generateC:
		std::cout << "Generating..." << std::endl;
		return generateC;
	case helpC:
		help();
		return helpC;
	case listNamesC:
		listNames();
		return listNamesC;
	case quitC:
		return quitC;
	case repositionC:
		reposition();
		return repositionC;
	}
	std::cout << "Command not found" << std::endl << std::endl;
	return invalidString;
}
void user::bindRectangle()
{
	if (rectangleRefrenceList.size() == 0)
	{
		std::cout << "No rectangles exist" << std::endl;
		return;
	}
	std::string userBindSpec;
	/*Creating a way to select a rectangle for the user to edit the data of*/
	std::cout << "What rectangle would you like to bind?" << std::endl;
	std::cin >> userBindSpec;
	bool found = false;
	for (unsigned int i = 0; i < rectangleRefrenceList.size(); i++)
	{
		if (userBindSpec == rectangleRefrenceList.at(i)->m_name)
		{
			rectPtr = rectangleRefrenceList.at(i);
			std::cout << "Quadrilateral " <<  rectangleRefrenceList.at(i)->m_name << " has been bound" << std::endl;
			found = true;
		}
	}
	if(!found)
	{
		std::cout << "Error: Rectangle not found" << std::endl;
	}
}
void user::clear()const/*Just learned that their is a library that allows you to clear the terminal. It is the stdlib.h file*/
{
	system("CLS");
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
	std::string userNaming;
	/*Needs to be able to specify values for the rectangle*/
	std::cout << "Name your rectangle/quadrilateral" << std::endl;
	std::cin >> userNaming;

	/*Checking to be sure that this name is not already taken*/
	for (unsigned int i = 0; i < rectangleRefrenceList.size(); i++)
	{
		if (userNaming == rectangleRefrenceList.at(i)->m_name)
		{
			std::cout << "FAILED: Rectangle name already exists" << std::endl;
			return NULL;
		}
	}

	char yN;
	std::cout << "Specify Coorinates?\nIf no, default coordinates will be set.\nType y/n: " << std::endl;
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
		rect* defaultRectangle = new rect(userNaming,tempVertexBufferPtr);
		rectPtr = defaultRectangle;/*Here lets just set the rect pointer to the reference
		of our new heap object because bind will probably end up being a function that cycles through a list of rectangle refrences anyways.*/
		rectangleRefrenceList.push_back(defaultRectangle);
		return defaultRectangle;/*I could store this in an internal vector but I would rather have it be held externally but I can't think of any methods to
								put it outside.*/
	}
	else if(yN == 'n')
	{
		rect* defaultRectangle = new rect(userNaming);
		rectPtr = defaultRectangle;/*Equivalent to binding it*/
		rectangleRefrenceList.push_back(defaultRectangle);
		return defaultRectangle;
	}
	else
	{
		std::cout << "ERROR: Invalid Input" << std::endl;
		return NULL;
	}
}
void user::deleteRectangle()
{
	std::string rectangleName;
	std::cout << "What rectangle would you like to delete?" << std::endl;
	std::cin >> rectangleName;
	unsigned int i = 0;
	while (i < rectangleRefrenceList.size() && rectangleRefrenceList.at(i)->m_name != rectangleName)
	{
		if (i == rectangleRefrenceList.size() - 1 && rectangleRefrenceList.at(i)->m_name != rectangleName)
		{
			std::cout << "Rectangle not found, couldn't delete rectangle" << std::endl;
			return;
		}
		i++;
	}
	/*Now how do I appropriately delete a vector member in the middle without having allocated memory in the middle of
	the vector. I am sure that the std::vector has a method for this. I think .erase is what we want*/
	rectangleRefrenceList.erase(rectangleRefrenceList.begin()+i);
	rectPtr = 0;/*We unbind the rectangle so display won't access the data even though it's unitialized*/
}
void user::display()const
{
	if (rectPtr != 0)
	{
		rectPtr->displayData();
	}
	else
		std::cout << "No rectangle is bound" << std::endl;
}
void user::help()const
{
	std::cout << commandArray[bindC] << "			Selects a different rectangle for the other commands to be used on" << std::endl;
	std::cout << commandArray[clearC] << "			Clears the text on the screen" << std::endl;
	std::cout << commandArray[colorC] << "			Allows you to specify new color values for your rectangles/quadraleteral" << std::endl;
	std::cout << commandArray[createRectangleC] << "		Creates a new rectangle and binds it" << std::endl;
	std::cout << commandArray[deleteC] << "			Deletes an existing rectangle/quadrilateral that the user inputs" << std::endl;
	std::cout << commandArray[displayC] << "			Displays all the data on the currently bound rectangle" << std::endl;
	std::cout << commandArray[generateC] << "		Draws all of your rectangles in a different window" << std::endl;
	std::cout << commandArray[helpC] << "			Displays all the commands that can be used" << std::endl;
	std::cout << commandArray[listNamesC] << "		Displays a list of all the rectangle names so far" << std::endl;
	std::cout << commandArray[quitC] << "			Quits the program without drawing anything" << std::endl;
	std::cout << commandArray[repositionC] << "		Allows user to reposition the verticies of their quadrilateral" << std::endl;
}
void user::listNames()const
{
	for (unsigned int i = 0; i < rectangleRefrenceList.size(); i++)
		std::cout << rectangleRefrenceList.at(i)->m_name << std::endl;
}
void user::reposition()
{
	vertex* rectangleVertexWriter = rectPtr->rectangleBuffPtr();
	for (int i = 0; i < 4; i++)/*I should prbably create a method that gets me the size of the rectangle buffer so if I make changes to the rectBuffer in the future I don't accidently try and write into unallocated memory*/
	{
		/*Maybe create restrictions that force it to be within a -1 and 1 value so it has to be on screen but I won't deal with that at the moment.*/
		std::cout << "Input an X value for the Vertex" << std::endl;
		std::cin >> (rectangleVertexWriter + i)->vX;
		std::cout << "Input a Y value for the Vertex" << std::endl;
		std::cin >> (rectangleVertexWriter + i)->vY;
	}
}