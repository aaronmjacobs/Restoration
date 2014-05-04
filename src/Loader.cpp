#include "Camera.h"
#include "FancyAssert.h"
#include "FlatSceneGraph.h"
#include "Geometry.h"
#include "IOUtils.h"
#include "lib/json/json.h"
#include "Light.h"
#include "Loader.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "PhongMaterial.h"
#include "Scene.h"
#include "SceneGraph.h"
#include "SceneObject.h"
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

/**********************************
 ** Protected (internal) loaders **
 **********************************/

SceneObjectData Loader::loadSceneObjectData(const Json::Value &root) {
   SceneObjectData data;

   // Name
   check("SceneObjectData", root, "name");
   data.name = root["name"].asString();

   // Position
   check("SceneObjectData", root, "position");
   Json::Value posVal = root["position"];
   check("SceneObjectData", posVal, "x");
   check("SceneObjectData", posVal, "y");
   check("SceneObjectData", posVal, "z");
   data.position.x = posVal["x"].asFloat();
   data.position.y = posVal["y"].asFloat();
   data.position.z = posVal["z"].asFloat();

   // Orientation
   check("SceneObjectData", root, "orientation");
   Json::Value oriVal = root["orientation"];
   check("SceneObjectData", oriVal, "w");
   check("SceneObjectData", oriVal, "x");
   check("SceneObjectData", oriVal, "y");
   check("SceneObjectData", oriVal, "z");
   data.orientation.w = oriVal["w"].asFloat();
   data.orientation.x = oriVal["x"].asFloat();
   data.orientation.y = oriVal["y"].asFloat();
   data.orientation.z = oriVal["z"].asFloat();

   // Scale
   check("SceneObjectData", root, "scale");
   Json::Value scaleVal = root["scale"];
   check("SceneObjectData", scaleVal, "x");
   check("SceneObjectData", scaleVal, "y");
   check("SceneObjectData", scaleVal, "z");
   data.scale.x = scaleVal["x"].asFloat();
   data.scale.y = scaleVal["y"].asFloat();
   data.scale.z = scaleVal["z"].asFloat();

   return data;
}

PhongMaterialData Loader::loadPhongMaterialData(SPtr<Scene> scene, const Json::Value &root) {
   PhongMaterialData data;

   // Shader program
   check("PhongMaterial", root, "shaderProgram");
   data.shaderProgram = loadShaderProgram(scene, root["shaderProgram"].asString());

   // Ambient color
   check("PhongMaterial", root, "ambient");
   Json::Value ambientValue = root["ambient"];
   check("PhongMaterial", ambientValue, "r");
   check("PhongMaterial", ambientValue, "g");
   check("PhongMaterial", ambientValue, "b");
   float ambientR = ambientValue["r"].asFloat();
   float ambientG = ambientValue["g"].asFloat();
   float ambientB = ambientValue["b"].asFloat();
   data.ambient = glm::vec3(ambientR, ambientG, ambientB);

   // Diffuse color
   check("PhongMaterial", root, "diffuse");
   Json::Value diffuseValue = root["diffuse"];
   check("PhongMaterial", diffuseValue, "r");
   check("PhongMaterial", diffuseValue, "g");
   check("PhongMaterial", diffuseValue, "b");
   float diffuseR = diffuseValue["r"].asFloat();
   float diffuseG = diffuseValue["g"].asFloat();
   float diffuseB = diffuseValue["b"].asFloat();
   data.diffuse = glm::vec3(diffuseR, diffuseG, diffuseB);

   // Specular color
   check("PhongMaterial", root, "specular");
   Json::Value specularValue = root["specular"];
   check("PhongMaterial", specularValue, "r");
   check("PhongMaterial", specularValue, "g");
   check("PhongMaterial", specularValue, "b");
   float specularR = specularValue["r"].asFloat();
   float specularG = specularValue["g"].asFloat();
   float specularB = specularValue["b"].asFloat();
   data.specular = glm::vec3(specularR, specularG, specularB);

   // Emission color
   check("PhongMaterial", root, "emission");
   Json::Value emissionValue = root["emission"];
   check("PhongMaterial", emissionValue, "r");
   check("PhongMaterial", emissionValue, "g");
   check("PhongMaterial", emissionValue, "b");
   float emissionR = emissionValue["r"].asFloat();
   float emissionG = emissionValue["g"].asFloat();
   float emissionB = emissionValue["b"].asFloat();
   data.emission = glm::vec3(emissionR, emissionG, emissionB);

   // Shininess
   check("PhongMaterial", root, "shininess");
   data.shininess = root["shininess"].asFloat();

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
   float phi = root["phi"].asFloat();
   float theta = root["theta"].asFloat();

   SPtr<Camera> camera = std::make_shared<Camera>(scene, data.name);
   camera->setPosition(data.position);
   camera->setOrientation(data.orientation);
   camera->setScale(data.scale);
   camera->setRotation(phi, theta);

   return camera;
}

SPtr<FlatSceneGraph> Loader::loadFlatSceneGraph(SPtr<Scene> scene, const Json::Value &root) {
   SPtr<FlatSceneGraph> graph = std::make_shared<FlatSceneGraph>();

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
      if (className == Light::CLASS_NAME) {
         SPtr<Light> light = loadLight(scene, objectVal);
         scene->addLight(light);
         sceneObject = light;
      } else if (className == Camera::CLASS_NAME) {
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
   // SceneObject
   SceneObjectData data = loadSceneObjectData(root);

   // Model
   check("Geometry", root, "model");
   SPtr<Model> model = loadModel(scene, root["model"]);

   SPtr<Geometry> geometry = std::make_shared<Geometry>(scene, model, data.name);
   geometry->setPosition(data.position);
   geometry->setOrientation(data.orientation);
   geometry->setScale(data.scale);

   return geometry;
}

SPtr<Light> Loader::loadLight(SPtr<Scene> scene, const Json::Value &root) {
   // SceneObject
   SceneObjectData data = loadSceneObjectData(root);

   // Color
   glm::vec3 color;
   check("Light", root, "color");
   Json::Value colorVal = root["color"];
   check("Light", colorVal, "r");
   check("Light", colorVal, "g");
   check("Light", colorVal, "b");
   color.r = colorVal["r"].asFloat();
   color.g = colorVal["g"].asFloat();
   color.b = colorVal["b"].asFloat();

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

SPtr<PhongMaterial> Loader::loadPhongMaterial(SPtr<Scene> scene, const std::string &fileName) {
   Json::Value root = IOUtils::readJsonFile(IOUtils::getPath<PhongMaterial>(fileName));

   PhongMaterialData data = loadPhongMaterialData(scene, root);

   return std::make_shared<PhongMaterial>(fileName, data.shaderProgram, data.ambient, data.diffuse, data.specular, data.emission, data.shininess);
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

   if (className == Geometry::CLASS_NAME) {
      return loadGeometry(scene, root);
   } else if (className == Light::CLASS_NAME) {
      return loadLight(scene, root);
   } else if (className == Camera::CLASS_NAME) {
      return loadCamera(scene, root);
   }

   ASSERT(false, "Invalid class name for SceneObject: %s", className.c_str());

   return SPtr<SceneObject>();
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
