#ifndef LOADER_H
#define LOADER_H

#include <string>

class aiScene;
namespace Assimp {
class Importer;
} // namespace Assimp

/**
 * Assists with the loading of content from files.
 */
namespace Loader {

/**
 * Loads am assimp scene with an importer from the specified file.
 */
const aiScene* loadScene(Assimp::Importer &importer, const std::string &fileName);

} // namespace Loader

#endif
