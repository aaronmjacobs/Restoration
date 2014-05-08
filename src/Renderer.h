#ifndef RENDERER_H
#define RENDERER_H

#include "FrameBuffer.h"
#include "GLMIncludes.h"
#include "MatrixStack.h"

class Scene;

/**
 * Manages the rendering of a scene.
 */
class Renderer {
protected:
   /**
    * Matrix stack of the model matrix.
    */
   MatrixStack modelMatrixStack;

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

   FrameBuffer fb;

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
    * Prepares the renderer for use, making any necessary OpenGL calls.
    */
   void prepare();

   /**
    * Renders the given scene.
    */
   void render(Scene &scene);
};

#endif
