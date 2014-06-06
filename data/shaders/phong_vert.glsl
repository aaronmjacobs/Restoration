#version 120

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uNormalMatrix;
uniform mat4 uDepthMVP;

attribute vec3 aPosition;
attribute vec3 aNormal;

varying vec3 vWorldPosition;
varying vec3 vNormal;
varying vec4 vShadowCoord;

void main() {
   // Transforms
   vec4 lPosition = uModelMatrix * vec4(aPosition.xyz, 1.0);
   vWorldPosition = lPosition.xyz;
   gl_Position = uProjMatrix * uViewMatrix * lPosition;
   vShadowCoord = uDepthMVP * vec4(aPosition, 1.0);

   // Calculate the relative normal
   vec4 lNormal = vec4(aNormal.xyz, 0.0);
   lNormal = uNormalMatrix * lNormal;
   vNormal = lNormal.xyz;
}