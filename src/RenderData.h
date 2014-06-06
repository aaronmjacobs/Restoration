#ifndef RENDER_DATA_H
#define RENDER_DATA_H

#include "FancyAssert.h"
#include "GLIncludes.h"
#include "GLMIncludes.h"

#include <map>
#include <string>

class RenderData {
protected:
   unsigned int state;
   std::map<std::string, GLint> intMap;
   std::map<std::string, GLuint> uintMap;
   std::map<std::string, glm::mat4> matMap;

public:
   RenderData();
   virtual ~RenderData();

   unsigned int getRenderState() const;
   GLint getGLint(const std::string &name) const;
   GLuint getGLuint(const std::string &name) const;
   glm::mat4 getMat(const std::string &name) const;

   void setRenderState(unsigned int state);
   void set(const std::string &name, GLint value);
   void set(const std::string &name, GLuint value);
   void set(const std::string &name, glm::mat4 value);
};

#endif
