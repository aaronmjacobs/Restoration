#version 120

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uNormalMatrix;

attribute vec3 aPosition;
attribute vec3 aNormal;
attribute vec2 aTexCoord;

varying vec3 vWorldPosition;
varying vec3 vNormal;
varying vec2 vTexCoord;
varying vec2 v_blurTexCoords[4];  

void main() {
  // Transforms
  vec4 lPosition = uModelMatrix * vec4(aPosition.x, aPosition.y, aPosition.z, 1);
  vWorldPosition = vec3(lPosition.x, lPosition.y, lPosition.z);
  gl_Position = uProjMatrix * uViewMatrix * lPosition;

  // Calculate the relative normal
  vec4 lNormal = vec4(aNormal.x, aNormal.y, aNormal.z, 0);
  lNormal = uNormalMatrix * lNormal;
  vNormal = vec3(lNormal.x, lNormal.y, lNormal.z);
  
  //Texturing
  vTexCoord = aTexCoord;
  
  v_blurTexCoords[0] = vTexCoord + vec2(0.0, -0.008);
  v_blurTexCoords[1] = vTexCoord + vec2(0.0, -0.004);
  v_blurTexCoords[2] = vTexCoord + vec2(0.0,  0.004);
  v_blurTexCoords[3] = vTexCoord + vec2(0.0,  0.008);
}