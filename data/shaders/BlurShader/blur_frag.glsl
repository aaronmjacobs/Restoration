/* blur_frag.glsl          */
/* Partial Author : Cameron Nouri  
   SEE README*/

uniform sampler2D uTexUnit;

varying vec2 vTexCoord;
varying vec2 v_blurTexCoords[8];

void main(void) {
  /* Set the fragment color to 0 */
  gl_FragColor = vec4(0.0);
  
  /* Blur the filter by using the automatically interpolated values from v_blurTexCoords */
  gl_FragColor += texture2D(uTexUnit, v_blurTexCoords[0])*0.0443683338718;
  gl_FragColor += texture2D(uTexUnit, v_blurTexCoords[1])*0.0776744219933;
  gl_FragColor += texture2D(uTexUnit, v_blurTexCoords[2])*0.115876621105;
  gl_FragColor += texture2D(uTexUnit, v_blurTexCoords[3])*0.147308056121;
  gl_FragColor += texture2D(uTexUnit, vTexCoord         )*0.159576912161;
  gl_FragColor += texture2D(uTexUnit, v_blurTexCoords[4])*0.147308056121;
  gl_FragColor += texture2D(uTexUnit, v_blurTexCoords[5])*0.115876621105;
  gl_FragColor += texture2D(uTexUnit, v_blurTexCoords[6])*0.0776744219933;
  gl_FragColor += texture2D(uTexUnit, v_blurTexCoords[7])*0.0443683338718;


}



  
  



