#version 120

uniform mat4 uProjMatrix;

attribute vec3 aPosition;
attribute vec2 aTexCoord;

varying vec2 vTexCoord;

void main() {
   vTexCoord = aTexCoord;
   gl_Position = uProjMatrix *  vec4(aPosition.xyz, 1.0);
}
