#version 150

in vec3 vertexColor;
in vec2 textureCoord;

out vec4 outColor;

uniform sampler2D textureSample;

void main()
{
	outColor = texture(textureSample, textureCoord);
}