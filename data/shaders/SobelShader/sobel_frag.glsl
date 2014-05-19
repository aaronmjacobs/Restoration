/* sobel_frag.glsl         */
/* Partial Author : Cameron Nouri  
   SEE README for thanks*/
z
uniform sampler2D uTexUnit;

varying vec2 vTexCoord;

void main(void) {



  vec4 TexColors = texture2D( uTexUnit, vTexCoord );


  /* Look at points AROUND the texture coordinate. Keep it consistant.
     we want horizontal, vertical values -/-, -/+, +/+, +/- Will use these
     for derivatives.*/
  vec4 s1 = texture2D( uTexUnit, vTexCoord - 1.0 / 300.0 - 1.0 / 200.0 );
  vec4 s2 = texture2D( uTexUnit, vTexCoord + 1.0 / 300.0 - 1.0 / 200.0 );

  vec4 s3 = texture2D( uTexUnit, vTexCoord - 1.0 / 300.0 + 1.0 / 200.0 );
  vec4 s4 = texture2D( uTexUnit, vTexCoord + 1.0 / 300.0 + 1.0 / 200.0 );

  /* Look at the x and y derivatives! */
  vec4 sx = 4.0 * ( ( s4 + s3 ) - ( s2 + s1 ) );
  vec4 sy = 4.0 * ( ( s2 + s4 ) - ( s1 + s3 ) );
  vec4 sobel = sqrt( sx * sx + sy * sy );
  
  /* If we want it grayscale and thresholded */
  /*float Threshold = .75f;
  if(sobel.r > Threshold && sobel.g > Threshold && sobel.b > Threshold)
     sobel = vec4(1.);
  else
     sobel = vec4(0.);*/

  gl_FragColor = sobel;
  


}

