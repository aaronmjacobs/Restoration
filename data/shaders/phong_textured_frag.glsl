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
uniform sampler2D uShadowMap;

varying vec3 vWorldPosition;
varying vec3 vNormal;
varying vec2 vTexCoord;
varying vec4 vShadowCoord;

float CalcShadowFactor(vec4 LightSpacePos) {
    vec3 ProjCoords = LightSpacePos.xyz / LightSpacePos.w;
    //ProjCoords = ProjCoords * 0.5 + vec3(0.5);
    vec2 UVCoords;
    UVCoords.x = 0.5 * ProjCoords.x + 0.5;
    UVCoords.y = 0.5 * ProjCoords.y + 0.5;
    float z = 0.5 * ProjCoords.z + 0.5;
    vec4 depthMap = texture2D(uShadowMap, UVCoords);
    float Depth = depthMap.z;
    float z_e = 2.0 * 1 / (100 + 1 - Depth * (100 - 1));

    if (Depth < (z - 0.001))
        return 0.5;
    else
        return 1.0;
}

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
      float falloff;
      if (uLights[i].linearFalloff == 0.0) {
        falloff = 1.0;
      } else {
        falloff = 1.0 / (uLights[i].constFalloff
                    + uLights[i].linearFalloff * lightDistance
                    + uLights[i].squareFalloff * lightDistance * lightDistance);
      }

      finalColor += (surfaceColor * diffuseAmount
                  + uMaterial.specular * specularAmount)
                  * falloff * uLights[i].color;
   }

   finalColor += surfaceColor * ((ambient + ambientGlobal) * 0.5) * 0.7;
   finalColor += uMaterial.emission;
   
   float bias = 0.105;
   float visibility = CalcShadowFactor(vShadowCoord);

   gl_FragColor = vec4(visibility * finalColor, 1.0);
}