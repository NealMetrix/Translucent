# Translucent

This branch I realized how bad it was to actually to have all the the OpenGL functions in the constructors of the rectangle class. Because it's OpenGL it has to be in a valid window context with glewInit called. But because I am asking for user input in a valid window context I am actually asking for user input while the window is partially generated. This results in an ugly white partially made window open in the background while the user is putting in information. The only way to fix this with my current understanding of OpenGL is to put all the OpenGL functions in a different class and then have it use whatever rectangles the user has generated to draw the rectangles based on the vertex buffers the user generated.

So my next steps are to actually move the user method calls to the top of the program and to move all of the openGL functions into their own class so they can render whatever buffers the user generates after the window is fully created. I am going have to do some thinking on what is the best way for the rectangle buffer instances and the OpenGL instances to interact with each other.

Starting to really realize why it can be so important to plan out the architecture of your code before hand since this is my second time trying to do some massive restructuring of my code.
