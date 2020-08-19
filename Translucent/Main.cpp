#include <iostream>
#include "Class_Code/Debugger.h"
/*includes the glew header file*/
#include <GLFW/glfw3.h>
#include <vector>

#include "Class_Code/UserInstances.h"
#include "Class_Code/renderObjects.h"
#include "Class_Code/color.h"
/*I need to have a place where I ame keeping track of all of my rectangle addresses for every single rectangle that's created.
Whenever I have a rectangle created I need it stored in this list. I need a way to find this address again so there is a way for me
to select the rectangle and then bind it. I could do this by passing a refrence in as a parameter to the bind what rectangle the user is looking at.
But then I run into my other problem. How does a user select a rectangle in the 1st place? Well we need to first know where the rectangle is? How
does the user specify what rectangle they want. To do that I need to give the user a way to name what the rectangle should be. This could be a number
or a string or a refrence. I can store them on the heap but I possibly don't have to. I can easily use the above vector to store all of these
rectangles but the big thing is how do I want the user to specify which one they want to select. Well I could use a while loop that cycles through
the vector and keeps looking for a match with some ID poperty that I allow the user to define. I can't help but wonder if there is a better algorithm
than a for or while loop but it will have to do for now.

And keep in mind I also still need to make sure that I still need to find a way to draw all of
these and write the shaders.

And I still need to separate the OpenGL from the rectangle object*/

int main()
{
    user mainUser;
    int tester = invalidString;
    while (tester != quitC && tester != generateC)
    {
        std::string mainInput;
        std::cout << std::endl << "Type a command to create or manipulate a rectangle\nType 'help' for the list of commands" << std::endl << std::endl;
        std::cin >> mainInput;
        tester = mainUser.input(mainInput);
        std::cout << std::endl;
    }

    if (tester == quitC)/*Making it so we don't generate the window if quit was the input*/
        return 0;

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

    unsigned int indices[] =
    {
        0,1,3,
        3,2,1
    };

    if (mainUser.rectangleRefrenceList.size() == 0)
        std::cout << "No rectangles to generate" << std::endl;
    /*There will be nothing displayed until I create a vertex buffer class that will use the rectangle class as
    a buffer.*/

    unsigned int indexID;
    GLError(glGenBuffers(1, &indexID));
    GLError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID));
    GLError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

    //vertex nullVert[] =
    //{
    //    {0.5f,0.5f},
    //    {0.5f,0.0f},
    //    {0.0f,0.0f},
    //    {0.0f,0.5f}
    //};
    //rect dummyRectangle("dummy", nullVert);

    /*renderObjects testRender(&dummyRectangle);/*The layout has to be specified before the shader is used.
                                                                   But then what buffer am I reading???Let's make a dummy rectangle
                                                                   to start the drawing. This didn't work. Why doesn't the dummy rectangle work?*/
    //std::cout << &dummyRectangle << std::endl;

    /*Okay so I still am not drawing anything on the screen but... I got rid of the asserts.
    It was actually how the parser was delivering our code. I didn't realize that it didn't include any enter
    keys that you type in the document... And sine there wasn't a space or an enter between #version 330 core and layout it errored out.
    I could have probably solved it with spaces but std::endl for every line it parsed in was probably better than placing spaces in
    by hand in the document for erroring out.
    But I told it to use the uniform from the user and they aren't giving it one!!! NO it should be set up to
    where it gives a default white square by default... But wait we haven't set the uniform so it can't use it yet!!*/
    //userShader.setUniform();
    /*GOT IT!!!!!!!!!!! Now I will comment out the dummy and see if it still works... And NO ASSERTS!!!!*/

    renderObjects renderRectangleList(mainUser.rectangleRefrenceList.at(0));/*This recreates the buffer every time. Not good OpenGL code but
                                                                            it would require me to do some restructuring again which I might do later
                                                                            or now if this doesn't work.*/
    /*If the user doesn't define a rectangle this will probably trigger an assert but I will try and deal with that later*/
    //renderObjects renderRectangleList(mainUser.rectangleRefrenceList.at(0));
    colors userShader("Graphics/Shaders/userRead.shader", mainUser.rectangleRefrenceList.at(0));
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLError(glClear(GL_COLOR_BUFFER_BIT));

        /*Now we need to do this but for every rectangle created by the user*/
        for(unsigned int i = 0; i < mainUser.rectangleRefrenceList.size(); i++)
        {
            renderRectangleList.reBuffer(mainUser.rectangleRefrenceList.at(i));
            renderRectangleList.renderRectangle();
            userShader.rewatch(mainUser.rectangleRefrenceList.at(i));
            userShader.setUniform();
            
            GLError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID));
            GLError(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
        }/*No errors but this doesn't work like I expected it too*/
        /*IT WORKS!!!!!!!!!!!!!*/

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}