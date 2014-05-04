varying vec3 vLightVector;
varying vec3 vNormal;

uniform sampler2D uTexUnit;
varying vec2 vTexCoord;



void main()
{

       vec4 texColor = texture2D(uTexUnit, vTexCoord);

       vec3 AmbientColor = vec3(0.3, 0.3, 0.3);
       vec3 DiffuseColor = texColor.xyz * clamp(dot(normalize(vNormal), normalize(vLightVector)), 0.0, 1.0);
       gl_FragColor = vec4(AmbientColor + DiffuseColor, 1.0);



}

