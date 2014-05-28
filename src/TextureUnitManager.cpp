#include "FancyAssert.h"
#include "TextureUnitManager.h"

namespace TextureUnitManager {

GLenum textureUnit;
GLint maxTextureUnits;

void reset() {
   glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
   ASSERT(maxTextureUnits > 0, "Max texture units is 0");
}

GLenum get() {
   ASSERT(textureUnit < maxTextureUnits, "No texture units available: %u / %d", textureUnit, maxTextureUnits);
   return textureUnit++;
}

void release() {
   ASSERT(textureUnit > 0, "No more texture units to release");
   --textureUnit;
}

}