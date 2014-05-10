#version 120

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

attribute vec3 aPosition;

varying vec3 vSkyboxCoord;

void main() {
  vec4 pos = uProjMatrix * uViewMatrix * uModelMatrix * vec4(aPosition.xyz, 1.0);
  gl_Position = pos.xyww; // Use W (1) for the Z so that the skybox is always at max distance
  
  vSkyboxCoord = aPosition;
}