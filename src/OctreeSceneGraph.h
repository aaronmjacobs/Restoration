#ifndef OCTREE_SCENE_GRAPH_H
#define OCTREE_SCENE_GRAPH_H

#include "SceneGraph.h"

class OctreeSceneGraph : public SceneGraph {
protected:

public:
   static const std::string CLASS_NAME;

   OctreeSceneGraph(SPtr<Scene> scene);
   virtual ~OctreeSceneGraph();
};

#endif
