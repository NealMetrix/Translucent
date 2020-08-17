#include <iostream>
#include "Resources/Debugger.h"/*includes the glew header file*/
#include <GLFW/glfw3.h>
#include <vector>
#include "Resources/UserInstances.h"/*includes the rectangle header*/
/*Okay so I need to find a way to have the user input to reference a rectangle.
I guess what I kinda need to do is have 1 single rect object bound to the user
object at a time. Or at least something like it. I think thats possible. We
could have the pointer be to any rect object and then we can change all the values
via the pointer. But that would mean that the user object doesn't create the rectangle objects
it would only manipulate them. We could have something else that generates rectangles for us,
buy honestly we probably just need a vector for all of these rectangles somewhere*/

static std::vector<rect*> rectangleList;/*Actually this doesn't create rectangles either... It just puts them in a dynamic array.
                                       Does this mean that I have to use heap allocation from a function. I can't think of
                                       another way to create a variable number of objects in the main function...
                                       But I could use this as a pointer to all the rectangles and use it to keep track of what
                                       objects I have deleted on the heap. Nah I'll just allocate them on the heap and have a function
                                       that returns their address when it's created so I can store it in a variable.*/

/*I need to finish the user method that creates new rectangles. But to do this I also need to create a constructor
for rectangles that generates a rectangle based on these buffer values.*/
int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current We foiund we gonna */
    glfwMakeContextCurrent(window);

    glewInit();

    float testBuffer[] =
    {
        0.0f,0.5f,
        0.5f, 0.0f,
        -0.5f, 0.0f
    };
    unsigned int indices[] =
    {
        0,1,3,
        3,2,1
    };
    /*This stops the window when it's midway open. Another structure error. I don't want to just have a white window just hanging there
    while the user enters information. I would like the window to be created after the user has entered there information.
    However to do that it means that I need to be able to create different buffers before the window creation happens.
    But the problem is that as I have written the code there would be a bunch of OpenGL errors because all gl functions
    need to be called in an valid window context after glewInit() has been called. So the gl functions in the rect constructors
    will have to be moved into a class of their own that draws on the rectangle buffers after the user has generated and manipulated
    all of the rectangles they so desire.*/
    user mainUser;
    int tester = invalidString;
    while (tester != quitC && tester != generateC)
    {
        std::cout << "Type a command to create or manipulate a rectangle\nType 'help' for the list of commands" << std::endl;
        std::string mainInput;
        std::cin >> mainInput;
        tester = mainUser.input(mainInput);
    }

    unsigned int indexID;
    glGenBuffers(1, &indexID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}