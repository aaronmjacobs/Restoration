#ifndef RENDERER_H
#define RENDERER_H

#include "Light.h"
#include "MatrixStack.h"
#include "Scene.h"
#include "ShaderProgram.h"

#include <list>

class SceneGraph;

/**
 * Manages the rendering of a scene.
 */
class Renderer {
private:
   /**
    * Matrix stack of the model matrix.
    */
   MatrixStack modelMatrixStack;

   /**
    * The view matrix.
    */
   glm::mat4 viewMatrix;

   /**
    * The projection matrix.
    */
   glm::mat4 projectionMatrix;

   /**
    * The field of view of the projection.
    */
   float fov;

public:
   /**
    * Constructs a renderer for a window with the given width and height, and
    * the desired field of view (in radians).
    */
   Renderer(int width, int height, float fov);

   /**
    * Does cleanup.
    */
   virtual ~Renderer();

   /**
    * Prepares the renderer for use, making any necessary OpenGL calls.
    */
   void prepare();

   /**
    * Handles window size changes.
    */
   void onWindowSizeChange(int width, int height);

   /**
    * Renders the given scene.
    */
   void render(Scene *scene);
};

#endif
