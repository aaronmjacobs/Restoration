#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "InputListener.h"
#include "Light.h"
#include "SceneGraph.h"
#include "ShaderProgram.h"
#include "TickListener.h"

#include "../CollisionHandler.h"

#include <list>

/**
 * A scene, composed of all objects in the scene (scene graph), the camera,
 * all lights, and all shader programs.
 */
class Scene {
private:
   /**
    * The scene graph (determines layout / hierarchy of items in the scene).
    */
   const SceneGraphRef sceneGraph;

   /**
    * The camera to view the scene through.
    */
   CameraRef camera;

   /**
    * All lights in the scene.
    */
   std::list<LightRef> lights;

   /**
    * All shader programs used in the scene.
    */
   std::list<ShaderProgramRef> shaderPrograms;

   /**
    * All items listening for user input.
    */
   std::list<InputListener*> inputListeners;

   /**
    * All items listening for ticks (not explicitly in the scene graph).
    */
   std::list<TickListener*> tickListeners;

   CollisionHandler collisionHandler;

public:
   /**
    * Creates a scene with the given scene graph.
    */
   Scene(SceneGraphRef sceneGraph, CameraRef camera);

   /**
    * Does cleanup.
    */
   virtual ~Scene();

   /**
    * Gets the scene graph.
    */
   SceneGraphRef getSceneGraph() {
      return sceneGraph;
   }

   /**
    * Gets the scene's camera.
    */
   CameraRef getCamera() {
      return camera;
   }

   /**
    * Gets the scene's lights.
    */
   const std::list<LightRef> getLights() {
      return lights;
   }

   /**
    * Gets the scene's shader programs.
    */
   const std::list<ShaderProgramRef> getShaderPrograms() {
      return shaderPrograms;
   }

   CollisionHandler* getCollisionHanlder() {
      return &collisionHandler;
   }

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
   void addLight(LightRef light);

   /**
    * Removes a light from the scene.
    */
   void removeLight(LightRef light);

   /**
    * Adds a shader program to the scene.
    */
   void addShaderProgram(ShaderProgramRef shaderProgram);

   /**
    * Removes a shader program from the scene.
    */
   void removeShaderProgram(ShaderProgramRef shaderProgram);

   /**
    * Adds an InputListener to the scene, to be notified of user input events.
    */
   void addInputListener(InputListener *listener);

   /**
    * Removes an InputListener from the scene.
    */
   void removeInputListener(InputListener *listener);

   /**
    * Adds a TickListener to the scene, to be called on each tick.
    */
   void addTickListener(TickListener *listener);

   /**
    * Removes a TickListener from the scene.
    */
   void removeTickListener(TickListener *listener);
};

#endif
