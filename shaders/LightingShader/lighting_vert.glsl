attribute vec3 aPosition;
attribute vec3 aNormal;
attribute vec2 aTexCoord;

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uNormalMatrix;

varying vec3 vLightVector;
varying vec3 vNormal;


varying vec2 vTexCoord;


void main()
{
    vec4 Position = uModelMatrix * vec4(aPosition, 1.0);
    vec4 Normal = vec4(aNormal, 1.0);
    vNormal = normalize((uNormalMatrix * Normal).xyz);
    
    vec3 LightPosition = vec3(3.0, 4.0, 5.0);
    vLightVector = LightPosition - Position.xyz;
    
    gl_Position = uProjMatrix * uViewMatrix * Position;
  
    vTexCoord = aTexCoord;

}

