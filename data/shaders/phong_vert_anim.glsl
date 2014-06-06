#version 120

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uNormalMatrix;
uniform mat4 bonesMatrix[64];
uniform mat4 uDepthMVP;

attribute vec3 aPosition;
attribute vec3 aNormal;
attribute vec2 aTexCoord;
attribute vec3 weights;
attribute vec3 joints;

varying vec3 vWorldPosition;
varying vec3 vNormal;
varying vec4 vShadowCoord;

void main() {
  // Animations
  mat4 animationMatrix =
    weights[0] * bonesMatrix[int(joints[0])] +
    weights[1] * bonesMatrix[int(joints[1])] +
    weights[2] * bonesMatrix[int(joints[2])];

  // Transforms
  vec4 lPosition = uModelMatrix * animationMatrix * vec4(aPosition, 1);
  vWorldPosition = vec3(lPosition.x, lPosition.y, lPosition.z);
  gl_Position = uProjMatrix * uViewMatrix * lPosition;
  vShadowCoord = uDepthMVP * vec4(aPosition, 1.0);

  // Calculate the relative normal
  vec4 lNormal = vec4(aNormal.x, aNormal.y, aNormal.z, 0);
  lNormal = uNormalMatrix * lNormal;
  vNormal = vec3(lNormal.x, lNormal.y, lNormal.z);
  
  //Texturing
   vTexCoord = aTexCoord;
}