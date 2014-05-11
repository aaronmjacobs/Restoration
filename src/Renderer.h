#ifndef RENDERER_H
#define RENDERER_H

#include "FrameBuffer.h"
#include "GLMIncludes.h"
#include "MatrixStack.h"

class Scene;
class Skybox;

/**
 * Manages the rendering of a scene.
 */
class Renderer {
protected:
   /**
    * Matrix stack of the model matrix.
    */
   MatrixStack modelMatrixStack;

   UPtr<FrameBuffer> fb;
   UPtr<Skybox> skybox;
   UPtr<Model> plane;

   /**
    * Setup the stencil buffer to generate the stencil
    */
   void prepareStencilDraw();

   /**
    * Prepare to draw the light world (using the generated stencil)
    */
   void prepareLightDraw();

   /**
    * Prepare to draw the dark world (with no stencil)
    */
   void prepareDarkDraw();

public:
   /**
    * Constructs a renderer for a window with the given width and height.
    */
   Renderer();

   /**
    * Does cleanup.
    */
   virtual ~Renderer();

   /**
    * Handles window size changes.
    */
   void onWindowSizeChange(int width, int height);

   /**
    * Prepares the renderer for use, making any necessary OpenGL calls.
    */
   void prepare(SPtr<Scene> scene);

   /**
    * Renders the given scene.
    */
   void render(Scene &scene);
};

#endif
