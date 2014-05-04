#ifndef LOADER_H
#define LOADER_H

#include "Types.h"

#include <assimp/Importer.hpp>
#include <map>
#include <string>

class aiScene;
class Camera;
class FlatSceneGraph;
class Geometry;
class Light;
class Material;
class Mesh;
class Model;
class PhongMaterial;
class Scene;
class SceneGraph;
class SceneObject;
class Shader;
class ShaderProgram;
class TextureMaterial;

namespace Json {
class Value;
} // namespace Json

namespace {
struct PhongMaterialData;
struct SceneObjectData;
} // namespace

typedef std::map<std::string, SPtr<Mesh>> MeshMap;
typedef std::map<std::string, SPtr<Shader>> ShaderMap;
typedef std::map<std::string, SPtr<ShaderProgram>> ShaderProgramMap;

/**
 * Assists with the loading of content from files.
 */
class Loader {
protected:
   static SPtr<Loader> instance;
   Assimp::Importer assimpImporter;
   MeshMap meshMap;
   ShaderMap shaderMap;
   ShaderProgramMap shaderProgramMap;

   Loader();
   void check(const std::string &type, const Json::Value &container, const std::string &key);
   PhongMaterialData loadPhongMaterialData(SPtr<Scene> scene, const Json::Value &root);
   SceneObjectData loadSceneObjectData(const Json::Value &root);

public:
   static SPtr<Loader> getInstance();
   static void resetSingleton();

   virtual ~Loader();

   /**
    * Loads am assimp scene with an importer from the specified file.
    */
   const aiScene* loadAssimpScene(const std::string &fileName);

   SPtr<Camera> loadCamera(SPtr<Scene> scene, const Json::Value &root);
   SPtr<FlatSceneGraph> loadFlatSceneGraph(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Geometry> loadGeometry(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Light> loadLight(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Material> loadMaterial(SPtr<Scene> scene, const std::string &fileName);
   SPtr<Mesh> loadMesh(const Json::Value &root);
   SPtr<Model> loadModel(SPtr<Scene> scene, const Json::Value &root);
   SPtr<PhongMaterial> loadPhongMaterial(SPtr<Scene> scene, const std::string &fileName);
   SPtr<Scene> loadScene(const std::string &fileName);
   SPtr<SceneGraph> loadSceneGraph(SPtr<Scene> scene, const Json::Value &root);
   SPtr<SceneObject> loadSceneObject(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Shader> loadShader(const Json::Value &root);
   SPtr<ShaderProgram> loadShaderProgram(SPtr<Scene> scene, const std::string &fileName);
   SPtr<TextureMaterial> loadTextureMaterial(SPtr<Scene> scene, const std::string &fileName);
};

#endif
