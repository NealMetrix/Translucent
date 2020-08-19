#Shader Vertex
#version 330 core

layout(location = 0) in vec4 rectangleBuff;/*Why is this a vec4 instead of a vec2*/

void main()
{
	gl_Position = vec4(rectangleBuff);
}

#Shader Fragment
#version 330 core

layout(location = 0) out vec4 color;
/*uniform is set up here I believe... or it might be set up in vertex and then the varying is outputted into the fragment shader*/

uniform vec4 userColorUniform;

void main()
{
	color = userColorUniform;/*The output value should be set here by the uniform*/
}