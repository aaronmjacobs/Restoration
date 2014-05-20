#version 120

uniform mat4 uProjMatrix;

attribute vec3 aPosition;
attribute vec2 aTexCoord;

varying vec2 vTexCoord;
varying vec2 v_blurTexCoords[16];

void main() {
   vTexCoord = aTexCoord;
   v_blurTexCoords[0] = vTexCoord + vec2(0.0, -0.016);
   v_blurTexCoords[1] = vTexCoord + vec2(0.0, -0.012);
   v_blurTexCoords[2] = vTexCoord + vec2(0.0, -0.008);
   v_blurTexCoords[3] = vTexCoord + vec2(0.0, -0.004);
   v_blurTexCoords[4] = vTexCoord + vec2(0.0,  0.004);
   v_blurTexCoords[5] = vTexCoord + vec2(0.0,  0.008);
   v_blurTexCoords[6] = vTexCoord + vec2(0.0,  0.012);
   v_blurTexCoords[7] = vTexCoord + vec2(0.0,  0.016);
   
   
   
   v_blurTexCoords[8] = vTexCoord + vec2(-0.016,  0.0);   
   v_blurTexCoords[9] = vTexCoord + vec2(-0.012, 0.0);
   v_blurTexCoords[10] = vTexCoord + vec2(-0.008, 0.0);
   v_blurTexCoords[11] = vTexCoord + vec2(-0.004,  0.0);
   v_blurTexCoords[12] = vTexCoord + vec2(0.004,  0.0);
   v_blurTexCoords[13] = vTexCoord + vec2(0.008,  0.0);
   v_blurTexCoords[14] = vTexCoord + vec2(0.012,  0.0);
   v_blurTexCoords[15] = vTexCoord + vec2(0.016,  0.0);   
   

   

   
   gl_Position = uProjMatrix *  vec4(aPosition.xyz, 1.0);
}
