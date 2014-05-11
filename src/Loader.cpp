#include "Camera.h"
#include "Character.h"
#include "Corona.h"
#include "Enemy.h"
#include "FancyAssert.h"
#include "FlatSceneGraph.h"
#include "Geometry.h"
#include "IOUtils.h"
#include "lib/json/json.h"
#include "Light.h"
#include "Loader.h"
#include "Magus.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "MovableObject.h"
#include "PhongMaterial.h"
#include "PhysicalObject.h"
#include "Player.h"
#include "Scene.h"
#include "SceneGraph.h"
#include "SceneObject.h"
#include "Scenery.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "TextureMaterial.h"

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <fstream>

namespace {

struct PhongMaterialData {
   glm::vec3 ambient, diffuse, specular, emission;
   float shininess;
   SPtr<ShaderProgram> shaderProgram;
};

struct SceneObjectData {
   std::string name;
   glm::vec3 position;
   glm::quat orientation;
   glm::vec3 scale;
};

} // namespace

SPtr<Loader> Loader::instance;

SPtr<Loader> Loader::getInstance() {
   if (!instance) {
      resetSingleton();
   }

   return instance;
}

void Loader::resetSingleton() {
   // Can't use make_shared due to protected constructor
   instance = SPtr<Loader>(new Loader);
}

Loader::Loader() {
}

Loader::~Loader() {
}

void Loader::check(const std::string &type, const Json::Value &container, const std::string &key) {
   ASSERT(container.isMember(key), "Missing key while loading %s: %s", type.c_str(), key.c_str());
}

bool Loader::isSceneObject(const std::string &className) {
   return className == SceneObject::CLASS_NAME || isGeometry(className) || isLight(className) || isCamera(className);
}

bool Loader::isLight(const std::string &className) {
   return className == Light::CLASS_NAME;
}

bool Loader::isCamera(const std::string &className) {
   return className == Camera::CLASS_NAME;
}

bool Loader::isGeometry(const std::string &className) {
   return className == Geometry::CLASS_NAME || isPhysicalObject(className);
}

bool Loader::isPhysicalObject(const std::string &className) {
   return className == PhysicalObject::CLASS_NAME || isScenery(className) || isMovableObject(className);
}

bool Loader::isScenery(const std::string &className) {
   return className == Scenery::CLASS_NAME;
}

bool Loader::isMovableObject(const std::string &className) {
   return className == MovableObject::CLASS_NAME || isCharacter(className);
}

bool Loader::isCharacter(const std::string &className) {
   return className == Character::CLASS_NAME || isPlayer(className) || isEnemy(className);
}

bool Loader::isPlayer(const std::string &className) {
   return className == Player::CLASS_NAME;
}

bool Loader::isEnemy(const std::string &className) {
   return className == Enemy::CLASS_NAME || isMagus(className) || isCorona(className);
}

bool Loader::isMagus(const std::string &className) {
   return className == Magus::CLASS_NAME;
}

bool Loader::isCorona(const std::string &className) {
   return className == Corona::CLASS_NAME;
}

/**********************************
 ** Protected (internal) loaders **
 **********************************/

glm::vec3 Loader::loadVec3(const Json::Value &root, bool rgb) {
   glm::vec3 vec;

   const std::string x = rgb ? "r" : "x";
   const std::string y = rgb ? "g" : "y";
   const std::string z = rgb ? "b" : "z";

   check("vec3", root, x);
   check("vec3", root, y);
   check("vec3", root, z);
   vec.x = root[x].asFloat();
   vec.y = root[y].asFloat();
   vec.z = root[z].asFloat();

   return vec;
}

glm::quat Loader::loadQuat(const Json::Value &root) {
   glm::quat quat;

   check("quat", root, "w");
   check("quat", root, "x");
   check("quat", root, "y");
   check("quat", root, "z");
   quat.w = root["w"].asFloat();
   quat.x = root["x"].asFloat();
   quat.y = root["y"].asFloat();
   quat.z = root["z"].asFloat();

   return quat;
}

PhongMaterialData Loader::loadPhongMaterialData(SPtr<Scene> scene, const Json::Value &root) {
   PhongMaterialData data;

   // Shader program
   check("PhongMaterial", root, "shaderProgram");
   data.shaderProgram = loadShaderProgram(scene, root["shaderProgram"].asString());

   // Ambient color
   check("PhongMaterial", root, "ambient");
   data.ambient = loadVec3(root["ambient"], true);

   // Diffuse color
   check("PhongMaterial", root, "diffuse");
   data.diffuse = loadVec3(root["diffuse"], true);

   // Specular color
   check("PhongMaterial", root, "specular");
   data.specular = loadVec3(root["specular"], true);

   // Emission color
   check("PhongMaterial", root, "emission");
   data.emission = loadVec3(root["emission"], true);

   // Shininess
   check("PhongMaterial", root, "shininess");
   data.shininess = root["shininess"].asFloat();
   
   return data;
}

SceneObjectData Loader::loadSceneObjectData(const Json::Value &root) {
   SceneObjectData data;

   // Name
   check("SceneObjectData", root, "name");
   data.name = root["name"].asString();

   // Position
   check("SceneObjectData", root, "position");
   data.position = loadVec3(root["position"]);

   // Orientation
   check("SceneObjectData", root, "orientation");
   data.orientation = loadQuat(root["orientation"]);

   // Scale
   check("SceneObjectData", root, "scale");
   data.scale = loadVec3(root["scale"]);

   return data;
}

/********************
 ** Public loaders **
 ********************/

const aiScene* Loader::loadAssimpScene(const std::string &fileName) {
   // Make sure the file exists and can be read
   std::ifstream ifile(fileName);
   ASSERT(ifile, "Unable to open file: %s", fileName.c_str());
   ifile.close();

   const aiScene* scene =
      assimpImporter.ReadFile(fileName, aiProcess_GenSmoothNormals |
                                        aiProcess_Triangulate);
   ASSERT(scene, "Unable to import scene: %s", fileName.c_str());

   return scene;
}

SPtr<Camera> Loader::loadCamera(SPtr<Scene> scene, const Json::Value &root) {
   // SceneObject
   SceneObjectData data = loadSceneObjectData(root);

   // Phi, theta
   check("Camera", root, "phi");
   check("Camera", root, "theta");
   check("Camera", root, "fov");
   float phi = root["phi"].asFloat();
   float theta = root["theta"].asFloat();
   float fov = root["fov"].asFloat();

   SPtr<Camera> camera = std::make_shared<Camera>(scene, fov, data.name);
   camera->setPosition(data.position);
   camera->setOrientation(data.orientation);
   camera->setScale(data.scale);
   camera->setRotation(phi, theta);

   return camera;
}

SPtr<Character> Loader::loadCharacter(SPtr<Scene> scene, const Json::Value &root) {
   check("Character", root, "@class");
   std::string className = root["@class"].asString();

   if (isPlayer(className)) {
      return loadPlayer(scene, root);
   } else if (isEnemy(className)) {
      return loadEnemy(scene, root);
   }

   ASSERT(false, "Invalid class name for Character: %s", className.c_str());

   return SPtr<Character>();
}

SPtr<Corona> Loader::loadCorona(SPtr<Scene> scene, const Json::Value &root) {
   // SceneObject
   SceneObjectData data = loadSceneObjectData(root);

   // Geometry
   check("Corona", root, "model");
   SPtr<Model> model = loadModel(scene, root["model"]);

   // MovableObject
   check("Corona", root, "velocity");
   glm::vec3 velocity = loadVec3(root["velocity"]);

   check("Corona", root, "acceleration");
   glm::vec3 acceleration = loadVec3("acceleration");

   // Character
   check("Corona", root, "health");
   int health = root["health"].asInt();

   SPtr<Corona> corona = std::make_shared<Corona>(scene, model, data.name);
   corona->setPosition(data.position);
   corona->setOrientation(data.orientation);
   corona->setScale(data.scale);
   corona->setVelocity(velocity);
   corona->setAcceleration(acceleration);
   corona->setHealth(health);

   return corona;
}

SPtr<Enemy> Loader::loadEnemy(SPtr<Scene> scene, const Json::Value &root) {
   check("Enemy", root, "@class");
   std::string className = root["@class"].asString();

   if (isMagus(className)) {
      return loadMagus(scene, root);
   } else if (isCorona(className)) {
      return loadCorona(scene, root);
   }

   ASSERT(false, "Invalid class name for Enemy: %s", className.c_str());

   return SPtr<Enemy>();
}

SPtr<FlatSceneGraph> Loader::loadFlatSceneGraph(SPtr<Scene> scene, const Json::Value &root) {
   SPtr<FlatSceneGraph> graph = std::make_shared<FlatSceneGraph>(scene);

   bool cameraLoaded = false;

   // Load each object
   check("FlatSceneGraph", root, "objects");
   Json::Value objectsVal = root["objects"];
   ASSERT(objectsVal.isArray(), "objects should be an array");
   for (int i = 0; i < objectsVal.size(); ++i) {
      Json::Value objectVal = objectsVal[i];
      check("FlatSceneGraph", objectVal, "@class");
      std::string className = objectVal["@class"].asString();

      SPtr<SceneObject> sceneObject;
      if (isLight(className)) {
         SPtr<Light> light = loadLight(scene, objectVal);
         scene->addLight(light);
         sceneObject = light;
      } else if (isCamera(className)) {
         ASSERT(!cameraLoaded, "Camera already loaded for scene graph");
         cameraLoaded = true;

         SPtr<Camera> camera = loadCamera(scene, objectVal);
         scene->setCamera(camera);
         sceneObject = camera;
      } else {
         sceneObject = loadSceneObject(scene, objectVal);
      }

      graph->add(sceneObject);
   }

   ASSERT(cameraLoaded, "No camera loaded for scene graph");

   return graph;
}

SPtr<Geometry> Loader::loadGeometry(SPtr<Scene> scene, const Json::Value &root) {
   check("Geometry", root, "@class");
   std::string className = root["@class"].asString();

   if (isPhysicalObject(className)) {
      return loadPhysicalObject(scene, root);
   }

   ASSERT(false, "Invalid class name for Geometry: %s", className.c_str());

   return SPtr<Geometry>();
}

SPtr<Light> Loader::loadLight(SPtr<Scene> scene, const Json::Value &root) {
   // SceneObject
   SceneObjectData data = loadSceneObjectData(root);

   // Color
   glm::vec3 color;
   check("Light", root, "color");
   color = loadVec3(root["color"], true);

   // Falloff
   check("Light", root, "constFalloff");
   check("Light", root, "linearFalloff");
   check("Light", root, "squareFalloff");
   float constFalloff = root["constFalloff"].asFloat();
   float linearFalloff = root["linearFalloff"].asFloat();
   float squareFalloff = root["squareFalloff"].asFloat();

   SPtr<Light> light = std::make_shared<Light>(scene, color, constFalloff, linearFalloff, squareFalloff, data.name);
   light->setPosition(data.position);
   light->setOrientation(data.orientation);
   light->setScale(data.scale);

   return light;
}

SPtr<Magus> Loader::loadMagus(SPtr<Scene> scene, const Json::Value &root) {
   // SceneObject
   SceneObjectData data = loadSceneObjectData(root);

   // Geometry
   check("Magus", root, "model");
   SPtr<Model> model = loadModel(scene, root["model"]);

   // MovableObject
   check("Magus", root, "velocity");
   glm::vec3 velocity = loadVec3(root["velocity"]);

   check("Magus", root, "acceleration");
   glm::vec3 acceleration = loadVec3("acceleration");

   // Character
   check("Magus", root, "health");
   int health = root["health"].asInt();

   SPtr<Magus> magus = std::make_shared<Magus>(scene, model, data.name);
   magus->setPosition(data.position);
   magus->setOrientation(data.orientation);
   magus->setScale(data.scale);
   magus->setVelocity(velocity);
   magus->setAcceleration(acceleration);
   magus->setHealth(health);

   return magus;
}

SPtr<Material> Loader::loadMaterial(SPtr<Scene> scene, const std::string &fileName) {
   Json::Value root = IOUtils::readJsonFile(IOUtils::getPath<Material>(fileName));
   check("Material", root, "@class");
   std::string className = root["@class"].asString();

   if (className == PhongMaterial::CLASS_NAME) {
      return loadPhongMaterial(scene, fileName);
   } else if (className == TextureMaterial::CLASS_NAME) {
      return loadTextureMaterial(scene, fileName);
   }
   
   ASSERT(false, "Invalid class name for Material: %s", className.c_str());

   return SPtr<Material>();
}

SPtr<Mesh> Loader::loadMesh(const Json::Value &root) {
   check("Mesh", root, "fileName");
   std::string fileName = root["fileName"].asString();

   MeshMap::iterator it = meshMap.find(fileName);
   if (it != meshMap.end()) {
      return it->second;
   }

   SPtr<Mesh> mesh(std::make_shared<Mesh>(fileName));
   meshMap[fileName] = mesh;

   return mesh;
}

SPtr<Model> Loader::loadModel(SPtr<Scene> scene, const Json::Value &root) {
   check("Model", root, "material");
   SPtr<Material> material = loadMaterial(scene, root["material"].asString());
   check("Model", root, "mesh");
   SPtr<Mesh> mesh = loadMesh(root["mesh"]);

   return std::make_shared<Model>(material, mesh);
}

SPtr<MovableObject> Loader::loadMovableObject(SPtr<Scene> scene, const Json::Value &root) {
   check("MovableObject", root, "@class");
   std::string className = root["@class"].asString();

   if (isCharacter(className)) {
      return loadCharacter(scene, root);
   }

   ASSERT(false, "Invalid class name for MovableObject: %s", className.c_str());

   return SPtr<MovableObject>();
}

SPtr<PhongMaterial> Loader::loadPhongMaterial(SPtr<Scene> scene, const std::string &fileName) {
   Json::Value root = IOUtils::readJsonFile(IOUtils::getPath<PhongMaterial>(fileName));

   PhongMaterialData data = loadPhongMaterialData(scene, root);

   return std::make_shared<PhongMaterial>(fileName, data.shaderProgram, data.ambient, data.diffuse, data.specular, data.emission, data.shininess);
}

SPtr<PhysicalObject> Loader::loadPhysicalObject(SPtr<Scene> scene, const Json::Value &root) {
   check("PhysicalObject", root, "@class");
   std::string className = root["@class"].asString();

   if (isMovableObject(className)) {
      return loadMovableObject(scene, root);
   } else if (isScenery(className)) {
      return loadScenery(scene, root);
   }

   ASSERT(false, "Invalid class name for PhysicalObject: %s", className.c_str());

   return SPtr<PhysicalObject>();
}

SPtr<Player> Loader::loadPlayer(SPtr<Scene> scene, const Json::Value &root) {
   // SceneObject
   SceneObjectData data = loadSceneObjectData(root);

   // Geometry
   check("Player", root, "model");
   SPtr<Model> model = loadModel(scene, root["model"]);

   // MovableObject
   check("Player", root, "velocity");
   glm::vec3 velocity = loadVec3(root["velocity"]);

   check("Player", root, "acceleration");
   glm::vec3 acceleration = loadVec3("acceleration");

   // Character
   check("Player", root, "health");
   int health = root["health"].asInt();

   SPtr<Player> player = std::make_shared<Player>(scene, model, data.name);
   player->setPosition(data.position);
   player->setOrientation(data.orientation);
   player->setScale(data.scale);
   player->setVelocity(velocity);
   player->setAcceleration(acceleration);
   player->setHealth(health);

   return player;
}

SPtr<Scene> Loader::loadScene(const std::string &fileName) {
   Json::Value root = IOUtils::readJsonFile(IOUtils::getPath<Scene>(fileName));

   SPtr<Scene> scene = std::make_shared<Scene>(fileName);

   // Loads the scene graph, including the camera, any lights, and any shader program
   check("Scene", root, "graph");
   SPtr<SceneGraph> graph = loadSceneGraph(scene, root["graph"]);
   scene->setSceneGraph(graph);

   return scene;
}

SPtr<SceneGraph> Loader::loadSceneGraph(SPtr<Scene> scene, const Json::Value &root) {
   check("SceneGraph", root, "@class");
   std::string className = root["@class"].asString();

   if (className == FlatSceneGraph::CLASS_NAME) {
      return loadFlatSceneGraph(scene, root);
   }

   ASSERT(false, "Invalid class name for SceneGraph: %s", className.c_str());   

   return SPtr<SceneGraph>();
}

SPtr<SceneObject> Loader::loadSceneObject(SPtr<Scene> scene, const Json::Value &root) {
   check("SceneObject", root, "@class");
   std::string className = root["@class"].asString();

   if (isGeometry(className)) {
      return loadGeometry(scene, root);
   } else if (isLight(className)) {
      return loadLight(scene, root);
   } else if (isCamera(className)) {
      return loadCamera(scene, root);
   }

   ASSERT(false, "Invalid class name for SceneObject: %s", className.c_str());

   return SPtr<SceneObject>();
}

SPtr<Scenery> Loader::loadScenery(SPtr<Scene> scene, const Json::Value &root) {
   // SceneObject
   SceneObjectData data = loadSceneObjectData(root);

   // Geometry
   check("Scenery", root, "model");
   SPtr<Model> model = loadModel(scene, root["model"]);

   SPtr<Scenery> scenery = std::make_shared<Scenery>(scene, model, data.name);
   scenery->setPosition(data.position);
   scenery->setOrientation(data.orientation);
   scenery->setScale(data.scale);

   return scenery;
}

SPtr<Shader> Loader::loadShader(const Json::Value &root) {
   check("Shader", root, "fileName");
   std::string fileName = root["fileName"].asString();

   ShaderMap::iterator it = shaderMap.find(fileName);
   if (it != shaderMap.end()) {
      return it->second;
   }

   check("Shader", root, "type");
   std::string typeName = root["type"].asString();
   GLenum type = 0;
   if (typeName == "vertex") {
      type = GL_VERTEX_SHADER;
   } else if (typeName == "fragment") {
      type = GL_FRAGMENT_SHADER;
   } else if (typeName == "geometry") {
      type = GL_GEOMETRY_SHADER;
   }
   ASSERT(type, "Invalid type name for shader: %s", typeName.c_str());

   SPtr<Shader> shader(std::make_shared<Shader>(type, fileName));
   shaderMap[fileName] = shader;

   return shader;
}

SPtr<ShaderProgram> Loader::loadShaderProgram(SPtr<Scene> scene, const std::string &fileName) {
   ShaderProgramMap::iterator it = shaderProgramMap.find(fileName);
   if (it != shaderProgramMap.end()) {
      return it->second;
   }

   SPtr<ShaderProgram> shaderProgram = std::make_shared<ShaderProgram>(fileName);
   Json::Value root = IOUtils::readJsonFile(IOUtils::getPath<ShaderProgram>(fileName));

   // Load each shader
   check("ShaderProgram", root, "shaders");
   Json::Value shadersVal = root["shaders"];
   ASSERT(shadersVal.isArray(), "shaders should be an array");
   for (int i = 0; i < shadersVal.size(); ++i) {
      shaderProgram->attach(loadShader(shadersVal[i]));
   }

   // Compile and link the shaders
   shaderProgram->compileShaders();
   shaderProgram->link();

   // Load all attributes
   check("ShaderProgram", root, "attributes");
   Json::Value attribsVal = root["attributes"];
   ASSERT(attribsVal.isArray(), "attributes should be an array");
   for (int i = 0; i < attribsVal.size(); ++i) {
      shaderProgram->addAttribute(attribsVal[i].asString());
   }

   // Load all uniforms
   check("ShaderProgram", root, "uniforms");
   Json::Value uniformsVal = root["uniforms"];
   ASSERT(uniformsVal.isArray(), "uniforms should be an array");
   for (int i = 0; i < uniformsVal.size(); ++i) {
      shaderProgram->addUniform(uniformsVal[i].asString());
   }

   shaderProgramMap[fileName] = shaderProgram;
   scene->addShaderProgram(shaderProgram);

   return shaderProgram;
}

SPtr<TextureMaterial> Loader::loadTextureMaterial(SPtr<Scene> scene, const std::string &fileName) {
   Json::Value root = IOUtils::readJsonFile(IOUtils::getPath<TextureMaterial>(fileName));

   PhongMaterialData data = loadPhongMaterialData(scene, root);

   // Texture
   check("TextureMaterial", root, "texture");
   std::string textureFileName = root["texture"].asString();

   return std::make_shared<TextureMaterial>(fileName, data.shaderProgram, data.ambient, data.diffuse, data.specular, data.emission, data.shininess, textureFileName);
}
