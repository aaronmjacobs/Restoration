/* original_frag.glsl          */
/* Author : Cameron Nouri      */

uniform sampler2D uTexUnit;
varying vec2 vTexCoord;

void main(void) {
  vec4 texColor1 = texture2D(uTexUnit, vTexCoord);
  gl_FragColor = vec4(texColor1[0], texColor1[1], texColor1[2], 1);
}
