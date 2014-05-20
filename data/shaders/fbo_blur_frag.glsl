#version 120

uniform sampler2D uTexture;

varying vec2 vTexCoord;
varying vec2 v_blurTexCoords[16];

void main() {
  vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);

  //finalColor += texture2D(uTexture, vTexCoord) * 0.185876621105;
  //finalColor += texture2D(uTexture, vTexCoord) * 0.185876621105;
  
  /* Y blur */
  finalColor += texture2D(uTexture, v_blurTexCoords[0]) * 0.115876621105;
  finalColor += texture2D(uTexture, v_blurTexCoords[1]) * 0.147308056121;  
  finalColor += texture2D(uTexture, v_blurTexCoords[2]) * 0.185876621105;
  finalColor += texture2D(uTexture, v_blurTexCoords[3]) * 0.227308056121;  
  finalColor += texture2D(uTexture, v_blurTexCoords[4]) * 0.227308056121;
  finalColor += texture2D(uTexture, v_blurTexCoords[5]) * 0.185876621105;
  finalColor += texture2D(uTexture, v_blurTexCoords[6]) * 0.147308056121;
  finalColor += texture2D(uTexture, v_blurTexCoords[7]) * 0.115876621105;
  
  /* X blur */
  finalColor += texture2D(uTexture, v_blurTexCoords[8]) * 0.115876621105;
  finalColor += texture2D(uTexture, v_blurTexCoords[9]) * 0.147308056121;
  finalColor += texture2D(uTexture, v_blurTexCoords[10]) * 0.185876621105;
  finalColor += texture2D(uTexture, v_blurTexCoords[11]) * 0.227308056121;  
  finalColor += texture2D(uTexture, v_blurTexCoords[12]) * 0.227308056121;
  finalColor += texture2D(uTexture, v_blurTexCoords[13]) * 0.185876621105;
  finalColor += texture2D(uTexture, v_blurTexCoords[14]) * 0.147308056121;
  finalColor += texture2D(uTexture, v_blurTexCoords[15]) * 0.115876621105;
  
  finalColor /= 6.0;
  finalColor += texture2D(uTexture, vTexCoord);
  
  gl_FragColor = vec4(finalColor);
}
