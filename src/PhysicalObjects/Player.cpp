#include "Player.h"

Player::Player(const std::string &jsonFileName, const std::string &name, ModelRef model)
: Character(jsonFileName, name, model) {

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
         spaceKey = true;
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
      }
      else if (key == GLFW_KEY_SPACE) {
         spaceKey = false;
      }
   }
}

void Player::onMouseButtonEvent(int button, int action) {
   if (button == GLFW_MOUSE_BUTTON_LEFT) {
      click = action == GLFW_PRESS;
   }
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
   if (spaceKey) {
      //jump
   }
   if (click) {
      //shoot something
      click = false;
   }
}