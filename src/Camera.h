#ifndef CAMERA_H
#define CAMERA_H

#include "SceneObject.h"

enum ControlMode { ANGLES, LOOKAT };

class Camera : public SceneObject {
protected:
   /**
    * Vertical look bounds to prevent camera from lining up with 'up' vector
    * (a little bit less than pi/2).
    */
   const float VERT_LOOK_BOUND = 1.5f;
   
   /**
    * The field of view of the projection.
    */
   float fov;

   int windowWidth, windowHeight;

   /**
    * Front facing vector.
    */
   glm::vec3 front;

   /**
    * Angles that define the orientation of the camera.
    */
   float phi, theta;

   glm::vec3 lookAt;

   /**
    * Updates the front facing vector based off of the phi and theta angles.
    */
   void updateFront();
   
   /**
    * The projection matrix.
    */
   glm::mat4 projectionMatrix;

   glm::mat4 shadowOrthoMatrix;
   glm::vec3 lightPos;
   bool shadowMode;

   ControlMode controlMode;
   bool won;

public:
   static const std::string CLASS_NAME;

   Camera(SPtr<Scene> const scene, float fov, const std::string &name = "");
   virtual ~Camera();
   
   glm::mat4 getProjectionMatrix();

   void setWon() {
      won = true;
   }
   
   /**
    * Handles window size changes.
    */
   void onWindowSizeChange(int width, int height);

   int getWindowWidth();
   int getWindowHeight();

   /**
    * Serializes the object to JSON.
    */
   virtual Json::Value serialize() const;

   void enableShadowMode(glm::vec3 position);
   void disableShadowMode();

   /**
    * Flys the camera by |amount| along the current front vector.
    */
   void fly(float amount);

   /**
    * Moves the camera along the x and z axes by |amount|, along the current
    * front vector.
    */
   void walk(float amount);

   /**
    * Moves the camera perpendicular to the front vector along the x and z axes
    * by |amount|.
    */
   void strafe(float amount);

   /**
    * Rotates the current orientation by the given angles (phi = pitch, theta
    * = yaw).
    */
   void rotateBy(float phi, float theta);

   void setRotation(float phi, float theta);

   void setLookAt(glm::vec3 lookAt);

   /**
    * Gets the current front-facing vector of the camera.
    */
   glm::vec3 getFront() const {
      return front;
   }

   /**
    * Gets the view matrix for the current position and orientation of the
    * camera.
    */
   glm::mat4 getViewMatrix();

   virtual void draw(const RenderData &renderData);

   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt);
};

#endif
