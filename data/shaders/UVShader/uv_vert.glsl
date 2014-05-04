attribute vec3 aPosition;
attribute vec2 aTexCoord;
uniform int PostProcessType;

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

varying vec3 vColor;
varying vec2 vTexCoord;


void main() {
  vec4 vPosition;

  /* First model transforms */
  vPosition = uModelMatrix* vec4(aPosition.x, aPosition.y, aPosition.z, 1);
  vPosition = uViewMatrix* vPosition;
  gl_Position = uProjMatrix*vPosition;

  vTexCoord = aTexCoord;
}
