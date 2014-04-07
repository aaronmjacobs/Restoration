#version 330

struct Light {
  vec3 position, color;
  float constFalloff, linearFalloff, squareFalloff;
};

struct Material {
  vec3 ambient, diffuse, specular, emission;
  float shininess;
};

uniform Light uLights[10];
uniform int uNumLights;
uniform Material uMaterial;
uniform vec3 uCameraPos;

in vec3 vWorldPosition;
in vec3 vNormal;

out vec4 outColor;

void main() {
  vec3 lNormal = normalize(vNormal);
  
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
  
    finalColor += ((uMaterial.diffuse * diffuseAmount
                  + uMaterial.specular * specularAmount) * falloff
                  + uMaterial.ambient) * uLights[i].color;
  }
  
  finalColor += uMaterial.emission;

  outColor = vec4(finalColor.r, finalColor.g, finalColor.b, 1);
}