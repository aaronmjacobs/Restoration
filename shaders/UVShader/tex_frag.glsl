
uniform sampler2D uTexUnit;
varying vec2 vTexCoord;

void main(void) {
  vec4 texColor1 = texture2D(uTexUnit, vTexCoord);
  gl_FragColor = vec4(vTexCoord.s, vTexCoord.t, 0, 1);
}
