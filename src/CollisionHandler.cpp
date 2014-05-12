#include "CollisionHandler.h"
#include "MovableObject.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Magus.h"
#include "Corona.h"
#include "Scenery.h"
#include "Vis.h"
#include "Justitia.h"
#include "Aegrum.h"

CollisionHandler::CollisionHandler(Scene &scene)
   : scene(scene) {
}

CollisionHandler::~CollisionHandler() {
}

void handleCollision(PhysicalObject &first, PhysicalObject &second) {
   // Default handler, does nothing
}

void CollisionHandler::handleCollision(Scenery &first, PhysicalObject &second) {
   // TODO Handle collision between an arbitrary immobile object, and an arbitrary mobile object
}

void CollisionHandler::handleCollision(MovableObject &first, MovableObject &second) {
   std::cout << "Colliding" << std::endl;
    
    
}

void CollisionHandler::handleCollision(Player &player, Enemy &enemy) {
    player.Character::setHealth(player.getHealth() - enemy.getAttackPower());

   BoundingBox collision = BoundingBox(player.getBounds(), enemy.getBounds());
   if (collision.width() < collision.height()) {
      enemy.reverseMovement();

      if (enemy.getPosition().x < player.getPosition().x) {
         player.setPosition(player.getPosition() + glm::vec3(1.0f, 0.0f, 0.0f));
      } else {
         player.setPosition(player.getPosition() + glm::vec3(-1.0f, 0.0f, 0.0f));
      }
   } else {
      if (enemy.getPosition().y < player.getPosition().y) {
         player.setPosition(player.getPosition() + glm::vec3(0.0f, 1.0f, 0.0f));
         player.setVelocity(glm::vec3(0.0f, 8.0f, 0.0f));
      } else {
         player.setPosition(player.getPosition() + glm::vec3(0.0f, -1.0f, 0.0f));
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
    glm::vec3 movementChange = glm::vec3(0.0f);
    glm::vec3 velocityChange = glm::vec3(0.0f);
    
    if (collisionWidth <= collisionHeight) {
        if (character.getPosition().x > scenery.getPosition().x) {
            //Hit from the right
            movementChange = glm::vec3(collisionWidth, 0.0f, 0.0f);
        } else {
            //Hit from the left
            movementChange = glm::vec3(-collisionWidth, 0.0f, 0.0f);
        }
        velocityChange = glm::vec3(0.0f, character.getVelocity().y, 0.0f);
    } else {
        if (character.getPosition().y > scenery.getPosition().y) {
            //Hit from above
            movementChange = glm::vec3(0.0f, collisionHeight, 0.0f);
            
            character.setOnGround();
        } else {
            //Hit from below
            movementChange = glm::vec3(0.0f, -collisionHeight, 0.0f);
        }
        velocityChange = glm::vec3(character.getVelocity().x, 0.0f, 0.0f);
    }
    character.translateBy(movementChange);
    character.setVelocity(velocityChange);
}

void CollisionHandler::handleCollision(Enemy &enemy, Scenery &scenery) {
   BoundingBox collision = BoundingBox(enemy.getBounds(), scenery.getBounds());

   if (collision.width() < collision.height()) {
      enemy.reverseMovement();
   }

   Character &character = enemy;
   handleCollision(character, scenery);
}

/*
void CollisionHandler::handleCollision(movingPlatform &movingPlatform, Scenery &scenery) {
    //Reverse moving direction
}*/

void CollisionHandler::handleCollision(Vis &vis, Scenery &scenery) {
    //Remove bullet from scene, both for players and enemies
    //Add shiny particle explosion if we want to later
    vis.removeVis();

}

//Separate handleCollisions for two different Vis types so that the attacker isn't hurt instantly when firing
void CollisionHandler::handleCollision(Justitia &justitia, Enemy &enemy) {
    enemy.setHealth(enemy.getHealth() - justitia.getAttackPower());
    justitia.removeVis();
}

void CollisionHandler::handleCollision(Aegrum &aegrum, Player &player) {
    player.setHealth(player.getHealth() - aegrum.getAttackPower());
    aegrum.removeVis();
}

//Incase we want to do a shiny collision explosion
void CollisionHandler::handleCollision(Justitia &justitia, Aegrum &aegrum) {
    justitia.removeVis();
    aegrum.removeVis();
}

void CollisionHandler::handleCollision(Vis &first, Vis &second) {
   //

}
