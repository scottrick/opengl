#version 150

in vec2 position;
in vec3 color;
in vec2 texture;

out vec3 vertexColor;
out vec2 textureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(position, 0.0, 1.0);
	vertexColor = color;
	textureCoord = texture;
}