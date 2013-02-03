#version 150

in vec2 position;
in float color;

out float vertexColor;

void main()
{
    gl_Position = vec4(position.x * 0.8, position.y * 1.8, 0.0, 1.0);
	vertexColor = color;
}