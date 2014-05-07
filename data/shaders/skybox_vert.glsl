#version 120

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

attribute vec3 aPosition;
attribute vec2 aSkyboxCoord;
varying vec2 vSkyboxCoord;

void main() {
  // Transforms
  vec4 lPosition = uModelMatrix * vec4(aPosition.x, aPosition.y, aPosition.z, 1);
  gl_Position = uProjMatrix * uViewMatrix * lPosition;
  
  vSkyboxCoord = aSkyboxCoord;
}