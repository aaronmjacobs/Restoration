#version 120
 
 void main(){
    gl_FragColor = vec4(gl_FragCoord.xyz, 1.0);
}