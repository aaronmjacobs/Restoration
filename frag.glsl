#version 330

smooth in vec3 color;
out vec4 outColor;

void main()
{
   outColor = vec4(color.r, color.g, color.b, 1.0);
}