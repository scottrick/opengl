#version 150

in vec3 vertexColor;
out vec4 outColor;

void main()
{
    outColor = vec4(vertexColor.r, vertexColor.g, vertexColor.b, 1.0);
}