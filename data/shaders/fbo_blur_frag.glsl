#version 120

uniform sampler2D uTexture;
uniform int uViewportWidth;
uniform int uViewportHeight;

varying vec2 vTexCoord;

const float BLUR = 2.0;
const int SPAN = 2;
const float SATURATION = 1.0;
const float EXPOSURE = 2.3;

void main() {
   float BLUR_SIZE_H = BLUR / uViewportWidth;
   float BLUR_SIZE_V = BLUR / uViewportHeight;

   vec4 sum = vec4(0.0);

   // Don't post process any invisible pixels (waste of time)
   vec4 textureColor = texture2D(uTexture, vTexCoord);
   if (textureColor.a == 0.0) {
      discard;
   }

   // Generate a blurred pixel
   int count = 0;
   for (int x = -SPAN; x <= SPAN; x++) {
      for (int y = -SPAN; y <= SPAN; y++) {
         if (length(vec2(float(x), float(y))) < SPAN) {
            vec2 diff = vec2(x * BLUR_SIZE_H, y * BLUR_SIZE_V);
            sum += texture2D(uTexture, vTexCoord + diff);
            ++count;
         }
      }
   }
   sum /= count;

   // Account for saturation and exposure of the blurred pixel
   float avg = (sum.r + sum.g + sum.b + sum.a) / 4.0;
   vec4 sumOffset = sum - vec4(avg);
   sum = vec4(avg) + sumOffset * SATURATION;
   sum *= EXPOSURE;

   // Multiply the pixel by its blurred value
   gl_FragColor = textureColor * sum;
}
