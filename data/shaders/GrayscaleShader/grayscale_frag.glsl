/* grayscale_frag.glsl          */
/* Author : Cameron Nouri  */

uniform sampler2D uTexUnit;
varying vec2 vTexCoord;

void main(void) {
  vec4 TexColors = texture2D( uTexUnit, vTexCoord );
  float GrayScaleAvg = 0.2126 * TexColors.r + 0.7152 * TexColors.g + 0.0722 * TexColors.b;
  gl_FragColor = vec4( GrayScaleAvg, GrayScaleAvg, GrayScaleAvg, 1.0 );
}
