#ifndef GEOMETRY_NODE_H
#define GEOMETRY_NODE_H

#include "SceneNode.h"

#include "GLIncludes.h"
#include "Model.h"
#include "ShaderProgram.h"

#include <memory>

class GeometryNode;
typedef std::shared_ptr<GeometryNode> GeometryNodeRef;

class GeometryNode : public SceneNode {
private:
   ModelRef model;

public:
   GeometryNode(SceneGraph *scene, const std::string &name, ModelRef model);
   virtual void draw(MatrixStack *matrixStack);
   virtual void tick(const double dt);
};

#endif