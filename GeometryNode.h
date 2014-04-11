#ifndef GEOMETRY_NODE_H
#define GEOMETRY_NODE_H

#include "SceneNode.h"

#include "GLIncludes.h"
#include "ShaderProgram.h"

#include <memory>

class GeometryNode;
typedef std::shared_ptr<GeometryNode> GeometryNodeRef;

class GeometryNode : public SceneNode {
private:
   const GLuint vao;
   const unsigned int numIndices;

public:
   static GeometryNodeRef fromFile(SceneGraph *graph, const std::string &name, const std::string &fileName, ShaderProgram *program);
   GeometryNode(SceneGraph *graph, const std::string &name, const GLuint vao, const unsigned int numIndices);
   virtual void draw(MatrixStack *matrixStack);
   virtual void tick(const double dt);
};

#endif