#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "../engine/Scene.h"

#include <iostream>

Player::Player(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model, Audio audio)
: Character(scene, jsonFileName, name, model) {
   acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
   audioPlayer = audio;
}

Player::~Player() {
}

void Player::onKeyEvent(int key, int action) {
   if (action == GLFW_PRESS) {
      if (key == GLFW_KEY_W) {
         wKey = true;
      }
      else if (key == GLFW_KEY_S) {
         sKey = true;
      }
      else if (key == GLFW_KEY_A) {
         aKey = true;
      }
      else if (key == GLFW_KEY_D) {
         dKey = true;
      }
      else if (key == GLFW_KEY_SPACE) {
         jump = true;
         audioPlayer.signalSound(SAMPLE_JUMP);
      }
   }
   else if (action == GLFW_RELEASE) {
      if (key == GLFW_KEY_W) {
         wKey = false;
      }
      else if (key == GLFW_KEY_S) {
         sKey = false;
      }
      else if (key == GLFW_KEY_A) {
         aKey = false;
      }
      else if (key == GLFW_KEY_D) {
         dKey = false;
      } else if (key == GLFW_KEY_SPACE) {
         jump = false;
      }
   }
}

void Player::onMouseButtonEvent(int button, int action) {
   if (button == GLFW_MOUSE_BUTTON_LEFT) {
      click = action == GLFW_PRESS;
   }
}

void Player::onMouseMotionEvent(double xPos, double yPos) {
}

void Player::tick(const float dt) {
   if (wKey) {
      //do whatever w does
   }
   if (aKey) {
      this->translateBy(glm::vec3(-1.0f * SPEED * dt, 0.0f, 0.0f));
   }
   if (sKey) {
      //do whatever s does
   }
   if (dKey) {
      this->translateBy(glm::vec3(SPEED * dt, 0.0f, 0.0f));
   }
   if (jump && onGround) {
      //jump
      jump = false;
      onGround = false;
      velocity += glm::vec3(0.0f, 500.0f, 0.0f) * dt;
   }
   if (click) {
      //shoot something
      click = false;
   }

   velocity += acceleration * dt;
   move(velocity * dt);

   // Platforms
   for (Platform *platform : Platform::allPlatforms) {
      if (checkCollision(platform)) {
         scene->getCollisionHanlder()->handleCollision(this, platform); // TODO
      }
   }

   // Enemies
   for (Enemy *enemy : Enemy::allEnemies) {
      if (checkCollision(enemy)) {
         scene->getCollisionHanlder()->handleCollision(this, enemy); // TODO
      }
   }
}

void Player::move(glm::vec3 dir) {
   // TODO
   translateBy(dir);
}

void Player::attack() {

}
