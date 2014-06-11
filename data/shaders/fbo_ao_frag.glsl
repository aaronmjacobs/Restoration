#version 120

uniform sampler2D uTexture;
uniform int uViewportWidth;
uniform int uViewportHeight;

varying vec2 vTexCoord;

const float BLUR = 2.0;
const int SPAN = 8;
const float SATURATION = 1.0;
const float EXPOSURE = 2.3;
const float THRESHOLD = 0.0065;

void main() {
   float BLUR_SIZE_H = BLUR / uViewportWidth;
   float BLUR_SIZE_V = BLUR / uViewportHeight;

   float sum = 0.0f;

   // Don't post process any invisible pixels (waste of time)
   vec4 textureColor = texture2D(uTexture, vTexCoord);
   float depth = textureColor.r;
   if (textureColor.a == 0.0 || depth == 1.0f) {
      discard;
   }

   // Generate a blurred pixel
   int count = 0;
   for (int x = -SPAN; x <= SPAN; x++) {
      for (int y = -SPAN; y <= SPAN; y++) {
         if (length(vec2(float(x), float(y))) < SPAN) {
            vec2 diff = vec2(x * BLUR_SIZE_H, y * BLUR_SIZE_V);
            float tempDepth = texture2D(uTexture, vTexCoord + diff).r;
            if(abs(depth - tempDepth) <= THRESHOLD) { 
               sum += tempDepth;
               ++count;
            }
         }
      }
   }
   
   float depthCol;
   
   if(count > 0) {
      sum /= count;
      
      sum = (sum - depth) + 1.0f;
      
      if(sum >= 1.0f) {
         sum = 1.0f;
      }
      
      if(sum <= 0.0f) {
         sum = 0.0f;
      }
      
      depthCol = pow(sum, 300);
   }
   else {
      depthCol = pow(depth, 300);
   }
   
   if(depthCol == 1.0f) {
      discard;
   }
   
   gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0f - depthCol);
}
