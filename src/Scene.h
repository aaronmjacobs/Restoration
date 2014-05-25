#ifndef SCENE_H
#define SCENE_H

#include "audio/Audio.h"
#include "CollisionHandler.h"
#include "InputListener.h"
#include "Saveable.h"
#include "TickListener.h"
#include "Types.h"

#include <list>

class Camera;
class Light;
class SceneGraph;
class ShaderProgram;
class Skybox;

class Scene : public Saveable, public TickListener {
protected:
   SPtr<SceneGraph> sceneGraph;
   SPtr<Skybox> lightSkybox;
   SPtr<Skybox> darkSkybox;
   WPtr<Camera> camera;
   WPtr<Player> player;
   std::list<WPtr<Light>> lights;
   std::list<WPtr<ShaderProgram>> shaderPrograms;
   CollisionHandler collisionHandler;
   SPtr<Audio> audio;
   bool editMode;

   /**
    * All items listening for user input.
    */
   std::list<SPtr<InputListener>> inputListeners;

   /**
    * All items listening for ticks (not explicitly in the scene graph).
    */
   std::list<SPtr<TickListener>> tickListeners;

public:
   static const std::string CLASS_NAME;
   static const std::string FOLDER_NAME;

   Scene(const std::string &jsonFileName);
   virtual ~Scene();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   void setEditMode(bool editMode);

   bool isInEditMode() {
      return editMode;
   }

   SPtr<Skybox> getLightSkybox();

   void setLightSkybox(SPtr<Skybox> lightSkybox);

   SPtr<Skybox> getDarkSkybox();

   void setDarkSkybox(SPtr<Skybox> darkSkybox);

   SPtr<SceneGraph> getSceneGraph();

   void setSceneGraph(SPtr<SceneGraph> sceneGraph);

   WPtr<Camera> getCamera();

   void setCamera(SPtr<Camera> camera);

   WPtr<Player> getPlayer();

   void setPlayer(SPtr<Player> player);

   const std::list<WPtr<Light>>& getLights();

   const std::list<WPtr<ShaderProgram>>& getShaderPrograms();

   CollisionHandler& getCollisionHanlder();

   void setAudio(SPtr<Audio> audio);

   SPtr<Audio> getAudio();

   void tick(const float dt);

   /**
    * Handles keyboard events.
    */
   void onKeyEvent(int key, int action);

   /**
    * Handles mouse click events.
    */
   void onMouseButtonEvent(int button, int action);

   /**
    * Handles mouse motion events.
    */
   void onMouseMotionEvent(double xPos, double yPos);

   /**
    * Handles window focus events.
    */
   void onWindowFocusGained();

   /**
    * Adds a light to the scene.
    */
   void addLight(SPtr<Light> light);

   /**
    * Removes a light from the scene.
    */
   void removeLight(SPtr<Light> light);

   /**
    * Adds a shader program to the scene.
    */
   void addShaderProgram(SPtr<ShaderProgram> shaderProgram);

   /**
    * Removes a shader program from the scene.
    */
   void removeShaderProgram(SPtr<ShaderProgram> shaderProgram);

   /**
    * Adds an InputListener to the scene, to be notified of user input events.
    */
   void addInputListener(SPtr<InputListener> listener);

   /**
    * Removes an InputListener from the scene.
    */
   void removeInputListener(SPtr<InputListener> listener);

   /**
    * Adds a TickListener to the scene, to be called on each tick.
    */
   void addTickListener(SPtr<TickListener> listener);

   /**
    * Removes a TickListener from the scene.
    */
   void removeTickListener(SPtr<TickListener> listener);
};

#endif
