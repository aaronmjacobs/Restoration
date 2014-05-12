#include "GLIncludes.h"
#include "Corona.h"
#include "Justitia.h"
#include "Magus.h"
#include "Player.h"
#include "Scene.h"
#include "SceneGraph.h"
#include "Scenery.h"
#include "Mesh.h"
#include "Material.h"
#include "Loader.h"
#include "Model.h"
#include "GLMIncludes.h"

const std::string Player::CLASS_NAME = "Player";

const int Player::BASE_HEALTH = 10;
const float Player::WALK_SPEED = 5.0f;
const float Player::JUMP_FORCE = 570.0f;

Player::Player(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
   : Character(scene, model, BASE_HEALTH, name) {
   wantsToGoLeft = wantsToGoRight = wantsToJump = wantsToAttack = false;
      facing = glm::vec3(1.0f, 0.0f, 0.0f);
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

SPtr<Model> Player::getBulletModel(SPtr<Scene> scene) {
   static SPtr<Model> bulletModel;

   if (bulletModel) {
      return bulletModel;
   }

   SPtr<Loader> loader = Loader::getInstance();
   SPtr<Mesh> mesh = std::make_shared<Mesh>("data/meshes/bullet.obj");
   SPtr<Material> material = loader->loadMaterial(scene, "otherMaterial");
   bulletModel = std::make_shared<Model>(material, mesh);
   return bulletModel;
}

void Player::tick(const float dt) {
   if (wantsToGoLeft) {
      facing = glm::vec3(-1.0f, 0.0f, 0.0f);
      position += glm::vec3(-WALK_SPEED * dt, 0.0f, 0.0f);
   }
   if (wantsToGoRight) {
      facing = glm::vec3(1.0f, 0.0f, 0.0f);
      position += glm::vec3(WALK_SPEED * dt, 0.0f, 0.0f);
   }

   if (wantsToJump && onGround) {
      onGround = false;
      velocity += glm::vec3(0.0f, JUMP_FORCE, 0.0f) * dt;
   }

   if (wantsToAttack) {
      // TODO Handle attack logic
      wantsToAttack = false;
      SPtr<Scene> sScene = scene.lock();
      if (sScene) {
         SPtr<Justitia> justitia = std::make_shared<Justitia>(sScene, getBulletModel(sScene));
         justitia->setRenderState(STENCIL_STATE | LIGHTWORLD_STATE);
         justitia->setPosition(getPosition() + facing + glm::vec3(0.0f, 0.25f, 0.0f));
         if (facing.x < 0) {
            justitia->setOrientation(glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
         }
         justitia->setVelocity(facing * 15.0f);
         sScene->getSceneGraph()->addPhys(justitia);
      }
   }
    
    if (!isAlive()) {
        markForRemoval();
    }

   position += velocity * dt + 0.5f * acceleration * dt * dt;
   velocity += acceleration * dt;
}

void Player::collideWith(PhysicalObject &other) {
   other.collideWith(*this);
}

void Player::collideWith(Scenery &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Player::collideWith(Player &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Player::collideWith(Magus &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Player::collideWith(Corona &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Player::collideWith(Justitia &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}

void Player::collideWith(Aegrum &other) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      sScene->getCollisionHanlder().handleCollision(*this, other);
   }
}
