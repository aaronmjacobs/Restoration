/* grayscale_vert.glsl          */
/* Author : Cameron Nouri  */

attribute vec3 aPosition;
attribute vec2 aTexCoord;

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

varying vec2 vTexCoord;


void main() {
  vec4 vPosition;

  /* First model transforms */
  vPosition = uModelMatrix* vec4(aPosition.x, aPosition.y, aPosition.z, 1);
  vPosition = uViewMatrix* vPosition;
  gl_Position = uProjMatrix*vPosition;

  /* Make sure to interpolate the TexCoords */
  vTexCoord = aTexCoord;
}
