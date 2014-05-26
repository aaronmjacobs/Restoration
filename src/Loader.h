#ifndef LOADER_H
#define LOADER_H

#include "GLIncludes.h"
#include "GLMIncludes.h"
#include "Types.h"

#include <assimp/Importer.hpp>
#include <map>
#include <string>

class Aegrum;
class aiScene;
class AniMesh;
class AniModel;
class Camera;
class Character;
class Corona;
class Enemy;
class FlatSceneGraph;
class FollowGeometry;
class Geometry;
class GridSceneGraph;
class Justitia;
class Light;
class Magus;
class Material;
class Mesh;
class Model;
class MovableObject;
class Obex;
class Player;
class PhongMaterial;
class PhysicalObject;
class Scene;
class SceneGraph;
class SceneObject;
class Scenery;
class Shader;
class ShaderProgram;
class SimpleMaterial;
class Skybox;
class SkyboxMaterial;
class TextureMaterial;
class Turris;
class Vagus;
class Vis;

namespace Json {
class Value;
} // namespace Json

namespace {
struct PhongMaterialData;
struct SceneObjectData;
} // namespace

typedef std::map<std::string, SPtr<AniMesh>> AniMeshMap;
typedef std::map<std::string, SPtr<Mesh>> MeshMap;
typedef std::map<std::string, SPtr<Shader>> ShaderMap;
typedef std::map<std::string, SPtr<ShaderProgram>> ShaderProgramMap;
typedef std::map<std::string, GLuint> TextureMap;

/**
 * Assists with the loading of content from files.
 */
class Loader {
protected:
   static UPtr<Loader> instance;
   Assimp::Importer assimpImporter;
   AniMeshMap aniMeshMap;
   MeshMap meshMap;
   ShaderMap shaderMap;
   ShaderProgramMap shaderProgramMap;
   TextureMap textureMap;

   Loader();
   void check(const std::string &type, const Json::Value &container, const std::string &key);
   bool isSceneObject(const std::string &className);
   bool isLight(const std::string &className);
   bool isCamera(const std::string &className);
   bool isGeometry(const std::string &className);
   bool isFollowGeometry(const std::string &className);
   bool isPhysicalObject(const std::string &className);
   bool isScenery(const std::string &className);
   bool isMovableObject(const std::string &className);
   bool isCharacter(const std::string &className);
   bool isPlayer(const std::string &className);
   bool isEnemy(const std::string &className);
   bool isMagus(const std::string &className);
   bool isCorona(const std::string &className);
   bool isObex(const std::string &className);
   bool isTurris(const std::string &className);
   bool isVagus(const std::string &className);
   bool isVis(const std::string &className);
   bool isJustitia(const std::string &className);
   bool isAegrum(const std::string &className);
   bool isMesh(const std::string &className);
   bool isAniMesh(const std::string &className);
   bool isModel(const std::string &className);
   bool isAniModel(const std::string &className);
   glm::vec3 loadVec3(const Json::Value &root, bool rgb = false);
   glm::quat loadQuat(const Json::Value &root);
   PhongMaterialData loadPhongMaterialData(SPtr<Scene> scene, const Json::Value &root);
   SceneObjectData loadSceneObjectData(const Json::Value &root);

public:
   static Loader& getInstance();
   static void resetSingleton();

   virtual ~Loader();

   /**
    * Loads am assimp scene with an importer from the specified file.
    */
   const aiScene* loadAssimpScene(const std::string &fileName);
   GLuint loadTexture(const std::string &fileName);
   GLuint loadCubemap(const std::string &fileName);

   SPtr<Aegrum> loadAegrum(SPtr<Scene> scene, const Json::Value &root);
   SPtr<AniMesh> loadAniMesh(const Json::Value &root);
   SPtr<AniModel> loadAniModel(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Camera> loadCamera(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Character> loadCharacter(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Corona> loadCorona(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Enemy> loadEnemy(SPtr<Scene> scene, const Json::Value &root);
   void loadFlatSceneGraph(SPtr<Scene> scene, const Json::Value &root);
   void loadGridSceneGraph(SPtr<Scene> scene, const Json::Value &root);
   SPtr<FollowGeometry> loadFollowGeometry(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Geometry> loadGeometry(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Justitia> loadJustitia(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Light> loadLight(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Magus> loadMagus(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Material> loadMaterial(SPtr<Scene> scene, const std::string &fileName);
   SPtr<Mesh> loadMesh(const Json::Value &root);
   SPtr<Model> loadModel(SPtr<Scene> scene, const Json::Value &root);
   SPtr<MovableObject> loadMovableObject(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Obex> loadObex(SPtr<Scene> scene, const Json::Value &root);
   SPtr<PhongMaterial> loadPhongMaterial(SPtr<Scene> scene, const std::string &fileName);
   SPtr<PhysicalObject> loadPhysicalObject(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Player> loadPlayer(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Scene> loadScene(const std::string &fileName);
   void loadSceneGraph(SPtr<Scene> scene, const Json::Value &root);
   SPtr<SceneObject> loadSceneObject(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Scenery> loadScenery(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Shader> loadShader(const Json::Value &root);
   SPtr<ShaderProgram> loadShaderProgram(SPtr<Scene> scene, const std::string &fileName);
   SPtr<SimpleMaterial> loadSimpleMaterial(SPtr<Scene> scene, const std::string &fileName);
   SPtr<Skybox> loadSkybox(SPtr<Scene> scene, const Json::Value &root);
   SPtr<SkyboxMaterial> loadSkyboxMaterial(SPtr<Scene> scene, const std::string &fileName);
   SPtr<TextureMaterial> loadTextureMaterial(SPtr<Scene> scene, const std::string &fileName);
   SPtr<Turris> loadTurris(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Vagus> loadVagus(SPtr<Scene> scene, const Json::Value &root);
   SPtr<Vis> loadVis(SPtr<Scene> scene, const Json::Value &root);
};

#endif
