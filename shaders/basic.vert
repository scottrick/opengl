#version 150

in vec2 position;
in vec3 color;

out vec3 vertexColor;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
	vertexColor = color;
}