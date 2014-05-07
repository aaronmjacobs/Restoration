#version 120

uniform samplerCube uSkybox;
varying vec2 vSkyboxCoord;

void main(void) {
  vec4 skyboxColor = texture2D(uSkybox, vSkyboxCoord);
  gl_FragColor = vec4(skyboxColor.xyz, 1);
}