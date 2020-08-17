#include <iostream>
#include "Resources/Debugger.h"
#include <GLFW/glfw3.h>
#include "Resources/Rectangle.h"

/*After programming this for awhile I came to realize that this is the perfect example of how
to not structure your code. I didn't think about how the user object would interact with the rectangle
object which means that this code needed massive restructuring. So I'll make a copy to rebuild*/

/*Trying to make an example with 2 translucent materials.
Let's make 2 objects with their own Render pipelines that can each take render values.*/

/*You have initialized the all of your class and have created ptr methods for rect properties.
You have initialized the userInput ptr to any char*, however this is designed to be something
that points to the properties of an instance of rect so in order to make this happen you will
have to do some creative casting to make it work. Although if we are going to do casting then maybe
we just want to cast a void pointer to whatever value is returned from the pointer methods of rect class

I am trying to think if I want to use just 1 vbo and just leave that bound. Regardless */

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
    /*Forward Alwasys to the stars We Got it */
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
    
    rect testRectangle;
    
    /*Note that index buffer can be bound before the vertexAtrribPointer layout but not before the vertex Array Object is bound
    The index buffer can even be bound before the vertex buffer but not the vertex array object.*/
    /*Just realized that if I wanted all of my recrtangles to be drawn the same way
    then it would be more efficient optimization wize to make this buffer in the main function
    and just make all vertex array objects use the same index buffer... So I am taking this out of my rect class
    because it is pretty useless to initialize the same data the same way but have a copy of that same data stored
    throughout multiple instances of a class.*/
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