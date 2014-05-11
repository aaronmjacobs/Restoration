#include "GLIncludes.h"
#include "Player.h"

const std::string Player::CLASS_NAME = "Player";

const int Player::BASE_HEALTH = 10;
const float Player::WALK_SPEED = 5.0f;
const float Player::JUMP_FORCE = 300.0f;

Player::Player(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
   : Character(scene, model, BASE_HEALTH, name) {
}

Player::~Player() {
}

Json::Value Player::serialize() const {
   Json::Value root = Character::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Player::onKeyEvent(int key, int action) {
   if (!isAlive()) {
      wantsToGoLeft = wantsToGoRight = wantsToJump = wantsToAttack = false;
      return;
   }

   if (action == GLFW_PRESS || action == GLFW_RELEASE) {
      bool press = action == GLFW_PRESS;

      if (key == GLFW_KEY_A) {
         wantsToGoLeft = press;
      } else if (key == GLFW_KEY_D) {
         wantsToGoRight = press;
      } else if (key == GLFW_KEY_SPACE) {
         wantsToJump = press;
      } else if (key == GLFW_KEY_ENTER) {
         wantsToAttack = press;
      }
   }
}

void Player::onMouseButtonEvent(int button, int action) {
}

void Player::onMouseMotionEvent(double xPos, double yPos) {
}

void Player::tick(const float dt) {
   if (wantsToGoLeft) {
      position += glm::vec3(-WALK_SPEED * dt, 0.0f, 0.0f);
   }
   if (wantsToGoRight) {
      position += glm::vec3(WALK_SPEED * dt, 0.0f, 0.0f);
   }

   if (wantsToJump && onGround) {
      onGround = false;
      velocity += glm::vec3(0.0f, JUMP_FORCE, 0.0f) * dt;
   }

   if (wantsToAttack) {
      // TODO Handle attack logic
   }

   position += velocity * dt + 0.5f * acceleration * dt * dt;
   velocity += acceleration * dt;
}

void Player::collideWith(PhysicalObject &other) {
   other.collideWith(*this);
}
