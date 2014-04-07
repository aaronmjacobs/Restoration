#ifndef MODEL_SCENE_NODE_H
#define MODEL_SCENE_NODE_H

#include "SceneNode.h"

#include "GLIncludes.h"
#include "ShaderProgram.h"

#include <memory>

class ModelSceneNode;
typedef std::shared_ptr<ModelSceneNode> ModelSceneNodeRef;

class ModelSceneNode : public SceneNode {
private:
   const GLuint vao;
   const unsigned int numIndices;

public:
   static ModelSceneNodeRef fromFile(SceneGraph *graph, const std::string &name, const std::string &fileName, ShaderProgram *program);
   ModelSceneNode(SceneGraph *graph, const std::string &name, const GLuint vao, const unsigned int numIndices);
   virtual void draw();
   virtual void tick();
};

#endif