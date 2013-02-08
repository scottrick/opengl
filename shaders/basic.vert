#version 150

in vec2 position;
in vec3 color;
in vec2 texture;

out vec3 vertexColor;
out vec2 textureCoord;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
	vertexColor = color;
	textureCoord = texture;
}