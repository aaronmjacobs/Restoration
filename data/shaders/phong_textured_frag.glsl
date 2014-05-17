#version 120

#define MAX_LIGHTS 10

struct Light {
  vec3 position, color;
  float constFalloff, linearFalloff, squareFalloff;
};

struct Material {
  vec3 ambient, diffuse, specular, emission;
  float shininess;
};

uniform Light uLights[MAX_LIGHTS];
uniform int uNumLights;
uniform Material uMaterial;
uniform vec3 uCameraPos;
uniform sampler2D uTexture;
uniform samplerCube uAmbientMap;
uniform sampler2D uAmbientGlobal;

varying vec3 vWorldPosition;
varying vec3 vNormal;
varying vec2 vTexCoord;

void main() {
   vec3 lNormal = normalize(vNormal);
   vec3 ambient = textureCube(uAmbientMap, lNormal).rgb;
   vec3 ambientGlobal = texture2D(uAmbientGlobal, vec2(0,0)).rgb;
   vec3 surfaceColor = texture2D(uTexture, vTexCoord).rgb;

   vec3 finalColor = vec3(0.0, 0.0, 0.0);
   for (int i = 0; i < uNumLights; ++i) {
      // Diffuse light
      vec3 toLight = uLights[i].position - vWorldPosition;
      float lightDistance = length(toLight);
      toLight = normalize(toLight);
      float nDotL = dot(lNormal, toLight);
      float diffuseAmount = max(nDotL, 0.0);

      // Specular light
      float specularAmount = 0.0;
      if (nDotL >= 0.0) {
         vec3 toCamera = normalize(uCameraPos - vWorldPosition);
         vec3 reflection = normalize(2.0 * nDotL * lNormal - toLight);
         specularAmount = pow(max(dot(toCamera, reflection), 0.0), uMaterial.shininess);
      }

      // Falloff
      float falloff = 1.0 / (uLights[i].constFalloff
                    + uLights[i].linearFalloff * lightDistance
                    + uLights[i].squareFalloff * lightDistance * lightDistance);

      finalColor += (surfaceColor * diffuseAmount
                  + uMaterial.specular * specularAmount)
                  * falloff * uLights[i].color;
   }

   finalColor += surfaceColor * ((ambient + ambientGlobal) * 0.5) * 0.5;
   finalColor += uMaterial.emission;

   gl_FragColor = vec4(finalColor.rgb, 1);
}