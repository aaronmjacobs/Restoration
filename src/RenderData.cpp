#include "RenderData.h"
#include "RenderState.h"

RenderData::RenderData() {
   state = NULL_STATE;
}

RenderData::~RenderData() {
}

unsigned int RenderData::getRenderState() const {
   return state;
}

GLint RenderData::getGLint(const std::string &name) const {
   ASSERT(intMap.count(name), "GLint not available: %s", name.c_str());
   return intMap.at(name);
}

GLuint RenderData::getGLuint(const std::string &name) const {
   ASSERT(uintMap.count(name), "GLuint not available: %s", name.c_str());
   return uintMap.at(name);
}

glm::mat4 RenderData::getMat(const std::string &name) const {
   ASSERT(matMap.count(name), "Mat not available : %s", name.c_str());
   return matMap.at(name);
}

void RenderData::setRenderState(unsigned int state) {
   this->state = state;
}

void RenderData::set(const std::string &name, GLint value) {
   intMap[name] = value;
}

void RenderData::set(const std::string &name, GLuint value) {
   uintMap[name] = value;
}

void RenderData::set(const std::string &name, glm::mat4 value) {
   matMap[name] = value;
}