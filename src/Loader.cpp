#include "Loader.h"

#include "FancyAssert.h"
#include "ModelSceneNode.h"
#include "SceneGraph.h"
#include "ShaderProgram.h"

#include <assimp/postprocess.h>     // Post processing flags

#include <fstream>

namespace Loader {

const aiScene* loadScene(Assimp::Importer *importer, const std::string &fileName) {
   // Make sure the file exists and can be read
   std::ifstream ifile(fileName);
   ASSERT(ifile, "Unable to open file: %s", fileName.c_str());
   ifile.close();

   const aiScene* scene =
      importer->ReadFile(fileName, aiProcess_GenSmoothNormals |
                                   aiProcess_Triangulate);
   ASSERT(scene, "Unable to import scene: %s", fileName.c_str());

   return scene;
}

} // namespace Loader