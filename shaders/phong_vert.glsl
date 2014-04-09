#version 330

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uNormalMatrix;

layout(location = 0)in vec3 aPosition;
layout(location = 1)in vec3 aNormal;

out vec3 vWorldPosition;
out vec3 vNormal;

void main() {
  // Transforms
  vec4 lPosition = uModelMatrix * vec4(aPosition.x, aPosition.y, aPosition.z, 1);
  vWorldPosition = vec3(lPosition.x, lPosition.y, lPosition.z);
  gl_Position = uProjMatrix * uViewMatrix * lPosition;

  // Calculate the relative normal
  vec4 lNormal = vec4(aNormal.x, aNormal.y, aNormal.z, 0);
  lNormal = uNormalMatrix * lNormal;
  vNormal = vec3(lNormal.x, lNormal.y, lNormal.z);
}