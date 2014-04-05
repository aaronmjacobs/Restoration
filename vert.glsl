#version 330

uniform mat4 uModelMatrix;

in vec3 position;
out vec3 color;

void main()
{
   color.r = position.x * 2.0;
   color.g = position.y * 2.0;
   color.b = position.x * -2.0;
   gl_Position = uModelMatrix * vec4(position, 1.0);
}