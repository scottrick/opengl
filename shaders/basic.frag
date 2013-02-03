#version 150

in float vertexColor;
out vec4 outColor;

void main()
{
    outColor = vec4(vertexColor, vertexColor, vertexColor, 1.0);
}