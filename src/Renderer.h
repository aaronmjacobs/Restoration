#ifndef RENDERER_H
#define RENDERER_H

#include "FrameBuffer.h"
#include "GLMIncludes.h"
#include "MatrixStack.h"
#include "RenderData.h"
#include "Shadow.h"

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

   RenderData renderData;

   UPtr<FrameBuffer> fb;
   UPtr<Model> plane;
   UPtr<Model> plane2;
   UPtr<Shadow> shadow;
   UPtr<Shadow> aoShadow;
   SPtr<ShaderProgram> shadowProgram;

   /**
   * Setup the shadoow buffer to draw to, and draw to it.
   */
   void prepareShadowDraw(Scene &scene);

   /**
   * Setup a version of the shadow buffer for AO.
   */
   void prepareAODraw();

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

   bool AO = false;

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

   void onMonitorChange();

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
