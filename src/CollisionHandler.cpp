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
   player.setHealth(player.getHealth() - enemy.getAttackPower());
   if (player.getInvFrames() <= 0.0f) {
      player.setInvFrames(2.0f);
   }

}

/*void CollisionHandler::handleCollision(Player &player, Corona &corona) {
    //player.setHealth(player.getHealth() - corona.getAttackPower());
    //corona.reverseMovement();
    //Add enemy logic for backing off after hurting you
}*/

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
      Particle::createEffect(scene, vis.getPosition(), glm::vec3(0.0f), false, 5.0f, 10, 3.0f, 25.0f, true);
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
         // TODO Determine health amount per enemy?
         LifeParticle::createEffect(scene, justitia.getPosition(), particleVelocity * 0.75f, 5.0f, 100, 15.0f, 4.0f, 5.0f);
      }
   } else {
      SPtr<Scene> scene = justitia.getScene().lock();
      if (scene) {
         Particle::createEffect(scene, justitia.getPosition(), glm::vec3(0.0f), false, 5.0f, 10, 3.0f, 25.0f, true);
      }
   }
}
COLLISION_REVERSE_FUNCTION(Justitia, Enemy)

void CollisionHandler::handleCollision(Aegrum &aegrum, Player &player) {
   player.setHealth(player.getHealth() - aegrum.getAttackPower());
   aegrum.markForRemoval();
   aegrum.setAttackPower(0);

   SPtr<Scene> scene = player.getScene().lock();
   if (scene) {
      Particle::createEffect(scene, player.getPosition(), glm::vec3(0.0f), false, 5.0f, 50, 3.0f, 25.0f, true);
   }
}
COLLISION_REVERSE_FUNCTION(Aegrum, Player)

