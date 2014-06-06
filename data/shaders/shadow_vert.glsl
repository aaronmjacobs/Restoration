#version 120
 
// Input vertex data, different for all executions of this shader.
attribute vec3 aPosition;
 
// Values that stay constant for the whole mesh.
uniform mat4 uDepthMVP;
 
void main(){
 gl_Position =  uDepthMVP * vec4(aPosition,1);
}