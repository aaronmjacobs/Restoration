#ifndef TICK_LISTENER_H
#define TICK_LISTENER_H

/**
 * Interface for receiving ticks.
 */
class TickListener {
public:
   /**
    * Steps |dt| seconds through time.
    */
   virtual void tick(const float dt) = 0;
};

#endif
