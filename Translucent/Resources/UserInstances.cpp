#include "UserInstances.h"
user::user(rect* ptr):rectPtr(ptr){}/*Note that any pointer can be automatically converted into a void pointer*/

/*I just realized while making all of this that I just gave the user only the ability to manipulate 1 rectangle. Any function that
I call won't override the rectangle, it will just manipulate whatever rectangle I passed into the constructor. Although this would be
a good idea on a possible way to create a method to rewrite any data you wrote on a previous rectangle*/
int user::input(std::string &inValue)
{
	int i;
	for (i = colorC; i <= quitC && inValue!=commandArray[i]; i++){}/*Loop where i value will be set to the index of the command array*/

	switch (i)
	{
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
/*Changing this to be something that pushes the vector*/
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
/*You know since this is really the only class that I need to access the rectangle class I could just make the entire class private
and allow some of these user methods to be friends of the rect class. This would allow us to access the rect class buffers directly
and it makes sense that we access them directly because I have already given them complete access with the pointers I returned
anyways.*/
void user::createRectangle()
{
	/*I could just cast the rectPtr to a vertex pointer but this way is safer because even if we accidently switch the order between*/
	vertex* rectangleVertexPtr = rectPtr->rectangleBuffPtr();

	/*You see the other method would have made it more robust code because if I say switch my rectangle class into something more
	like a hexagon class for whatever reason I end up making it so I can access the buffer directly instead of the methods that
	just return pointers and this would allow me to do the sizeof() method on the buffer for this for loop. I could do this the exact
	opposite though. It could be that this reaches into a rect instance by having a method in the rect class that takes a user instance
	as a parameter. I could also use this method to create a rect object on the heap*/


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