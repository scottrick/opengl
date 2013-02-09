#version 150

in vec3 vertexColor;
in vec2 textureCoord;

out vec4 outColor;

uniform sampler2D textureOne;
uniform sampler2D textureTwo;
uniform float time;

void main()
{
	if (textureCoord.y > 0.5f) {
		vec2 newCoords;
		newCoords.y = 1.0f - textureCoord.y;
		newCoords.x = textureCoord.x + (sin(textureCoord.y * 20.0f + time * 2.0f) * 0.05f);
		
		vec4 colorOne = texture(textureOne, newCoords);
		vec4 colorTwo = texture(textureTwo, vec2(newCoords.x, textureCoord.y));
		outColor = mix(colorOne, colorTwo, (sin(time) + 1.0f) / 2.0f);
	}
	else {
		vec4 colorOne = texture(textureTwo, textureCoord);
		vec4 colorTwo = texture(textureOne, textureCoord);
		outColor = mix(colorOne, colorTwo, 0.5f);
	}

	
	// vec4 colorOne = texture(textureOne, textureCoord);
	// vec4 colorTwo = texture(textureTwo, textureCoord);
	// outColor = mix(colorOne, colorTwo, (sin(time) + 1.0f) / 2.0f);
}