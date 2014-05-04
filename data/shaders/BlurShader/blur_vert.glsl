/* blur_vert.glsl          */
/* Partial Author : Cameron Nouri  
   SEE README*/

attribute vec3 aPosition;
attribute vec2 aTexCoord;
uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

varying vec2 vTexCoord;
varying vec2 v_blurTexCoords[8];  

void main() {
  vec4 vPosition;

  /* First model transforms */
  vPosition = uModelMatrix* vec4(aPosition.x, aPosition.y, aPosition.z, 1);
  vPosition = uViewMatrix* vPosition;
  gl_Position = uProjMatrix*vPosition;

  vTexCoord = aTexCoord;
  
  /* Set up Gaussian Blur -- or a form of it. Wanted the blur to be noticable but still run
     on lower end machines. */
  v_blurTexCoords[0] = vTexCoord + vec2(0.0, -0.016);
  v_blurTexCoords[1] = vTexCoord + vec2(0.0, -0.012);
  v_blurTexCoords[2] = vTexCoord + vec2(0.0, -0.008);
  v_blurTexCoords[3] = vTexCoord + vec2(0.0, -0.004);
  v_blurTexCoords[4] = vTexCoord + vec2(0.0,  0.004);
  v_blurTexCoords[5] = vTexCoord + vec2(0.0,  0.008);
  v_blurTexCoords[6] = vTexCoord + vec2(0.0,  0.012);
  v_blurTexCoords[7] = vTexCoord + vec2(0.0,  0.016);
  
}


