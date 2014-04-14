#ifndef LOADER_H
#define LOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <string>

/**
 * Assists with the loading of content from files.
 */
namespace Loader {

/**
 * Loads am assimp scene with an importer from the specified file.
 */
const aiScene* loadScene(Assimp::Importer *importer, const std::string &fileName);

} // namespace Loader

#endif
