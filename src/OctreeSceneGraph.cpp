#include "OctreeSceneGraph.h"

const std::string OctreeSceneGraph::CLASS_NAME = "OctreeSceneGraph";

OctreeSceneGraph::OctreeSceneGraph(SPtr<Scene> scene)
: SceneGraph(scene) {

}

OctreeSceneGraph::~OctreeSceneGraph() {
}