#ifndef SKYBOX_H
#define SKYBOX_H

#include "GLIncludes.h"
#include "Serializable.h"

#include <string>

class Model;

class Skybox : public Serializable {
protected:
   GLuint skyboxID, ambientMapID, ambientGlobalID;
   GLint uSkybox;
   SPtr<Model> model;
   const std::string name;

public:
   static const std::string CLASS_NAME;

   Skybox(SPtr<Model> model, const std::string &name);
   virtual ~Skybox();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   void renderSkybox(RenderData &renderData);

   GLuint getSkyboxID() {
      return skyboxID;
   }

   GLuint getAmbientMapID() {
      return ambientMapID;
   }
};

#endif