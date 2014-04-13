#ifndef LOADER_H
#define LOADER_H

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure

#include <string>

namespace Loader {

const aiScene* loadScene(Assimp::Importer *importer, const std::string &fileName);

} // namespace Loader

#endif