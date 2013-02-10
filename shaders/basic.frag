#version 150

in vec3 vertexColor;
in vec2 textureCoord;

out vec4 outColor;

uniform sampler2D textureOne;
uniform sampler2D textureTwo;
uniform float time;

void main()
{
	vec4 colorOne = texture(textureTwo, textureCoord);
	vec4 colorTwo = texture(textureOne, textureCoord);
	vec4 textureColor = mix(colorOne, colorTwo, (sin(time * 2.0f) + 1.0f) / 2.0f);
	
	outColor = vec4(vertexColor, 1.0f) * textureColor;
}