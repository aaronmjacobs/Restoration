#include "CollisionHandler.h"
#include "CollisionsIncludes.h"
#include "LifeParticle.h"

#define COLLISION_REVERSE_FUNCTION(FIRST_CLASS, SECOND_CLASS) \
void CollisionHandler::handleCollision(SECOND_CLASS &second, FIRST_CLASS &first) {\
   handleCollision(first, second);\
}

CollisionHandler::CollisionHandler(Scene &scene)
   : scene(scene) {
}

CollisionHandler::~CollisionHandler() {
}

void CollisionHandler::handleCollision(PhysicalObject &first, PhysicalObject &second) {
   // Default handler, does nothing
}

void CollisionHandler::handleCollision(Player &player, Enemy &enemy) {
   if (!player.isInvincible()) {
      SPtr<Scene> scene = player.getScene().lock();
      if (scene) {
         Particle::createEffect(scene,
                                player.getPosition(),         // Position
                                glm::vec3(0.0f),              // Velocity
                                false,                        // Gravity enabled
                                5.0f,                         // Size
                                enemy.getAttackPower() * 10,  // Number of particles
                                5.0f,                         // Duration (seconds)
                                enemy.getAttackPower(),       // Particle spread
                                true);                        // Stencil mode
      }

      player.setHealth(player.getHealth() - enemy.getAttackPower());
      player.setInvincibilityTime(2.0f);

      if (!player.isAlive()) {
         SPtr<Scene> sScene = player.getScene().lock();
         if (sScene) {
            Particle::createEffect(sScene,
                                   player.getPosition(), // Position
                                   glm::vec3(0.0f),   // Velocity
                                   false,             // Gravity enabled
                                   5.0f,              // Size
                                   500,                // Number of particles
                                   3.0f,              // Duration (seconds)
                                   40.0f,             // Particle spread
                                   true);             // Stencil mode
         }
      }
   }
}

void CollisionHandler::handleCollision(Enemy &enemy1, Enemy &enemy2) {
   //Reverse direction
   enemy1.reverseMovement();
   enemy2.reverseMovement();
}

void CollisionHandler::handleCollision(Character &character, Scenery &scenery) {
   BoundingBox collision = BoundingBox(character.getBounds(), scenery.getBounds());
   float collisionWidth = collision.width();
   float collisionHeight = collision.height();
   glm::vec3 characterPos = character.getPosition();
   glm::vec3 sceneryPos = scenery.getPosition();
   glm::vec3 characterVel = character.getVelocity();
   glm::vec3 characterMove(0.0f);

   if (collisionWidth <= collisionHeight) {
      // Avoid getting stuck on edges
      if (collisionHeight < 0.1f) {
         return;
      }

      // Treat the collision in x
      if (characterPos.x >= sceneryPos.x) {
         // Character is to the right
         characterMove.x = collisionWidth;
         if (characterVel.x < 0.0f) {
            characterVel.x = 0.0f;
         }
      } else {
         // Character is to the left
         characterMove.x = -collisionWidth;
         if (characterVel.x > 0.0f) {
            characterVel.x = 0.0f;
         }
      }
   } else {
      // Treat the collision in y
      if (characterPos.y >= sceneryPos.y) {
         // Character is above
         characterMove.y = collisionHeight;
         if (characterVel.y < 0.0f) {
            characterVel.y = 0.0f;
            character.setOnGround();
         }
      } else {
         // Character is below
         characterMove.y = -collisionHeight;
         if (characterVel.y > 0.0f) {
            characterVel.y = 0.0f;
         }
      }
   }

   character.translateBy(characterMove);
   character.setVelocity(characterVel);
}

COLLISION_REVERSE_FUNCTION(Character, Scenery)

void CollisionHandler::handleCollision(Obex &obex, Scenery &scenery) {
   BoundingBox collision = BoundingBox(obex.getBounds(), scenery.getBounds());
   float collisionWidth = collision.width();
   float collisionHeight = collision.height();
   glm::vec3 obexPos = obex.getPosition();
   glm::vec3 sceneryPos = scenery.getPosition();
   glm::vec3 obexVel = obex.getVelocity();
   glm::vec3 obexMove(0.0f);

   obex.setStoppedStatus(true);
   obex.setSavedVel(-obexVel);
   obex.resetAttackTime();
   if (collisionWidth <= collisionHeight) {
      // Avoid getting stuck on edges
      if (collisionHeight < 0.1f) {
         return;
      }

      // Treat the collision in x
      if (obexPos.x >= sceneryPos.x) {
         // Character is to the right
         obexMove.x = collisionWidth;
         if (obexVel.x < 0.0f) {
            obexVel.x = 0.0f;
         }
      } else {
         // obex is to the left
         obexMove.x = -collisionWidth;
         if (obexVel.x > 0.0f) {
            obexVel.x = 0.0f;
         }
      }
   } else {
      // Treat the collision in y
      if (obexPos.y >= sceneryPos.y) {
         // Character is above
         obexMove.y = collisionHeight;
         if (obexVel.y < 0.0f) {
            obexVel.y = 0.0f;
            //obex.setOnGround();
         }
      } else {
         // Character is below
         obexMove.y = -collisionHeight;
         if (obexVel.y > 0.0f) {
            obexVel.y = 0.0f;
         }
      }
   }
   
   Character& obexCharacter = obex;
   handleCollision(obexCharacter, scenery);
}

COLLISION_REVERSE_FUNCTION(Obex, Scenery)

void CollisionHandler::handleCollision(Vis &vis, Scenery &scenery) {
   vis.markForRemoval();

   SPtr<Scene> scene = vis.getScene().lock();
   if (scene) {
      Particle::createEffect(scene,
                             vis.getPosition(), // Position
                             glm::vec3(0.0f),   // Velocity
                             false,             // Gravity enabled
                             5.0f,              // Size
                             10,                // Number of particles
                             3.0f,              // Duration (seconds)
                             25.0f,             // Particle spread
                             true);             // Stencil mode
   }
}

COLLISION_REVERSE_FUNCTION(Vis, Scenery)

void CollisionHandler::handleCollision(Corona &corona, Scenery &scenery) {
   BoundingBox collision = BoundingBox(corona.getBounds(), scenery.getBounds());
   float collisionWidth = collision.width();
   float collisionHeight = collision.height();
   glm::vec3 coronaPos = corona.getPosition();
   glm::vec3 sceneryPos = scenery.getPosition();
   glm::vec3 coronaVel = corona.getVelocity();
   glm::vec3 coronaMove(0.0f);

   if (collisionWidth <= collisionHeight) {
      // Avoid getting stuck on edges
      if (collisionHeight < 0.1f) {
         return;
      }

      // Treat the collision in x
      if (coronaPos.x >= sceneryPos.x) {
         // Character is to the right
         coronaMove.x = collisionWidth;
         if (coronaVel.x < 0.0f) {
            corona.reverseMovement();
         }
      } else {
         // Character is to the left
         coronaMove.x = -collisionWidth;
         if (coronaVel.x > 0.0f) {
            corona.reverseMovement();
         }
      }
   }
   Character& coronaCharacter = corona;
   handleCollision(coronaCharacter, scenery);

}

COLLISION_REVERSE_FUNCTION(Corona, Scenery)

void CollisionHandler::handleCollision(Justitia &justitia, Enemy &enemy) {
   enemy.setHealth(enemy.getHealth() - justitia.getAttackPower());
   justitia.markForRemoval();
   justitia.setAttackPower(0);

   if (!enemy.isAlive()) {
      glm::vec3 particleVelocity = justitia.getVelocity();
      SPtr<Scene> scene = justitia.getScene().lock();
      if (scene) {
         LifeParticle::createEffect(scene,
            justitia.getPosition(),                // Position
            particleVelocity,              // Velocity
            5.0f,                                  // Size
            enemy.getHealthReplenishment() * 10,   // Number of particles
            15.0f,                                 // Duration (seconds)
            enemy.getHealthReplenishment(),        // Particle spread
            enemy.getHealthReplenishment());       // Total health amount
      }
   } else {
      SPtr<Scene> scene = justitia.getScene().lock();
      if (scene) {
         Particle::createEffect(scene,
                                justitia.getPosition(),  // Position
                                glm::vec3(0.0f),         // Velocity
                                false,                   // Gravity enabled
                                5.0f,                    // Size
                                10,                      // Number of particles
                                3.0f,                    // Duration (seconds)
                                25.0f,                   // Particle spread
                                true);                   // Stencil mode
      }
   }
}

COLLISION_REVERSE_FUNCTION(Justitia, Enemy)

void CollisionHandler::handleCollision(Aegrum &aegrum, Player &player) {
   if (!player.isInvincible()) {
      SPtr<Scene> scene = player.getScene().lock();
      if (scene) {
         Particle::createEffect(scene,
                                player.getPosition(),           // Position
                                glm::vec3(0.0f),                // Velocity
                                false,                          // Gravity enabled
                                5.0f,                           // Size
                                aegrum.getAttackPower() * 10,   // Number of particles
                                5.0f,                           // Duration (seconds)
                                aegrum.getAttackPower(),        // Particle spread
                                true);                          // Stencil mode
      }

      player.setHealth(player.getHealth() - aegrum.getAttackPower());
      player.setInvincibilityTime(2.0f);

      if (!player.isAlive()) {
         SPtr<Scene> sScene = player.getScene().lock();
         if (sScene) {
            Particle::createEffect(sScene,
                                   player.getPosition(), // Position
                                   glm::vec3(0.0f),   // Velocity
                                   false,             // Gravity enabled
                                   5.0f,              // Size
                                   500,                // Number of particles
                                   3.0f,              // Duration (seconds)
                                   40.0f,             // Particle spread
                                   true);             // Stencil mode
         }
      }
   }

   aegrum.markForRemoval();
   aegrum.setAttackPower(0);
}
COLLISION_REVERSE_FUNCTION(Aegrum, Player)

