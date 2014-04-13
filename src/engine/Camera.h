#ifndef CAMERA_H
#define CAMERA_H

#include "GLIncludes.h"
#include "GLMIncludes.h"

/**
 * Class that represents a camera in the game world.
 */
class Camera {
private:
   /**
    * Vertical look bounds to prevent camera from lining up with 'up' vector
    * (a little bit less than pi/2).
    */
   const float VERT_LOOK_BOUND = 1.5f;

   /**
    * Position of the camera, and front facing vector.
    */
   glm::vec3 position, front;

   /**
    * Angles that define the orientation of the camera.
    */
   float phi, theta;

   /**
    * Updates the front facing vector based off of the phi and theta angles.
    */
   void updateFront();

public:
   /**
    * Creates a camera on origin, facing down the z axis.
    */
   Camera();

   /**
    * Does cleanup (currently nothing!).
    */
   ~Camera();

   /**
    * Translates the camera by the given vector.
    */
   void translateBy(glm::vec3 trans);

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
   void rotate(float phi, float theta);

   /**
    * Gets the current position of the camera.
    */
   glm::vec3 getPosition() {
      return position;
   }

   /**
    * Gets the current front-facing vector of the camera.
    */
   glm::vec3 getFront() {
      return front;
   }

   /**
    * Gets the view matrix for the current position and orientation of the
    * camera.
    */
   glm::mat4 getViewMatrix();
};

#endif