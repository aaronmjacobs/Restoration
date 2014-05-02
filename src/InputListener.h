#ifndef INPUT_LISTENER_H
#define INPUT_LISTENER_H

/**
 * Interface for handling user input events.
 */
class InputListener {
public:
   /**
    * Called on keyboard events.
    */
   virtual void onKeyEvent(int key, int action) = 0;

   /**
    * Called on mouse button click events.
    */
   virtual void onMouseButtonEvent(int button, int action) = 0;

   /**
    * Called on mouse motion events.
    */
   virtual void onMouseMotionEvent(double xPos, double yPos) = 0;
};

#endif
