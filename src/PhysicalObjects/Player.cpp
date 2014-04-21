#include "Player.h"
#include "Platform.h"
#include "Bullet.h"
#include "Enemy.h"
#include "../engine/Scene.h"

#include "../serialization/Serializer.h"

#include <iostream>

ModelRef bulletModel;
bool right;
int lastHealth;

Player::Player(Scene *scene, const std::string &jsonFileName, const std::string &name, ModelRef model, Audio audio)
: Character(scene, jsonFileName, name, model) {
   acceleration = glm::vec3(0.0f, -9.8f, 0.0f);
   bulletModel = ModelSerializer::load("bullet.json", scene);
   audioPlayer = audio;
   lastHealth = health;
}

Player::~Player() {
}

void Player::onKeyEvent(int key, int action) {
   if (isDead()) {
      wKey = sKey = right = aKey = dKey = jump = false;
      return;
   }
   if (action == GLFW_PRESS) {
      if (key == GLFW_KEY_W) {
         wKey = true;
      }
      else if (key == GLFW_KEY_S) {
         sKey = true;
      }
      else if (key == GLFW_KEY_A) {
         right = false;
         aKey = true;
      }
      else if (key == GLFW_KEY_D) {
         right = true;
         dKey = true;
      }
      else if (key == GLFW_KEY_SPACE) {
         jump = true;
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
   if (isDead()) {
      wKey = sKey = right = aKey = dKey = jump = false;
      return;
   }
   if (button == GLFW_MOUSE_BUTTON_LEFT) {
      click = action == GLFW_PRESS;
   }
}

void Player::onMouseMotionEvent(double xPos, double yPos) {
}

bool playedEndSound;
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
      audioPlayer.signalSound(SAMPLE_JUMP);
      jump = false;
      onGround = false;
      velocity += glm::vec3(0.0f, 500.0f, 0.0f) * dt;
   }
   if (click) {
      audioPlayer.signalSound(SAMPLE_SHOOT);

      // Bullet
      AxisAlignedBoundingBox boundsBullet;
      boundsBullet.xMin = bulletModel->getMesh()->getMinX();
      boundsBullet.xMax = bulletModel->getMesh()->getMaxX();
      boundsBullet.yMin = bulletModel->getMesh()->getMinY();
      boundsBullet.yMax = bulletModel->getMesh()->getMaxY();
      
      glm::vec3 bulletVel = glm::vec3(10.0f, 0.0f, 0.0f);;
      if (!right) {
         bulletVel *= -1.0f;
      }

      BulletRef bullet = std::make_shared<Bullet>(scene, "", "bullet0", bulletModel, bulletVel);
      bullet->setBounds(boundsBullet);

      if (!right) {
         bullet->rotateBy(glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
      }

      bullet->translateBy(position);
      scene->getSceneGraph()->addChild(bullet);
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
   bool anyAlive = false;
   for (Enemy *enemy : Enemy::allEnemies) {
      if (!enemy->alive) {
         continue;
      }
      anyAlive = true;
      if (checkCollision(enemy)) {
         scene->getCollisionHanlder()->handleCollision(this, enemy); // TODO
      }
   }

   if (!anyAlive && !playedEndSound) {
      playedEndSound = true;
      audioPlayer.signalSound(SAMPLE_WIN);
      std::cout << "You win! :D" << std::endl;
   }

   if (lastHealth != getHealth()) {
      lastHealth = getHealth();
      audioPlayer.signalSound(SAMPLE_OW);
   }

   if (isDead() && !playedEndSound) {
      playedEndSound = true;
      audioPlayer.signalSound(SAMPLE_LOSE);
      std::cout << "You died D:" << std::endl;
   }
}

void Player::move(glm::vec3 dir) {
   // TODO
   translateBy(dir);
}

void Player::attack() {

}
