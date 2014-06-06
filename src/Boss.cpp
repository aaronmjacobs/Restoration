#include "GLIncludes.h"
#include "Loader.h"
#include "SceneGraph.h"

#include "CollisionsIncludes.h"

const std::string Boss::CLASS_NAME = "Boss";

const float Boss::BASE_HEALTH = 50.0f;
const float Boss::HOVER_SPEED = 4.0f;
const float Boss::HEALTH_REPLACEMENT = 10.0f;
const float Boss::ATTACK_POWER = 15.0f;
float Boss::ATTACK_TIME = 6.0f;

//Put health in the creation of Magus, and damage
Boss::Boss(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Enemy(scene, model, BASE_HEALTH, HEALTH_REPLACEMENT, ATTACK_POWER, name) {
}

Boss::~Boss() {
}

Json::Value Boss::serialize() const {
   Json::Value root = Enemy::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Boss::tick(const float dt) {
   SPtr<Scene> sScene = scene.lock();
   if (sScene) {
      SPtr<Player> player = sScene->getPlayer().lock();
      if (player) {
         glm::vec3 playerPos = player->getPosition();
         glm::vec3 shootVec = glm::normalize(playerPos - position);

         /*if (glm::length(position - playerPos) < 25.0f) {
            if (ATTACK_TIME < 2 && ATTACK_TIME > 0) {
               //Chase a bit
               glm::vec3 chaseVec = glm::normalize(playerPos - position);
               setVelocity(chaseVec + chaseVec + chaseVec + chaseVec);
            }
            else if (ATTACK_TIME > 0) {
               //Continue attacking
            }
            else {
               ATTACK_TIME = 6.0f;

               float aegrumCreationDistance = 0.5f;
               float aegrumSpeed = 7.0f;
               glm::vec3 aegrumPos = position + shootVec * aegrumCreationDistance;

               Loader &loader = Loader::getInstance();
               Json::Value modelValue;
               modelValue["@class"] = "Model";
               modelValue["material"] = "aegrum";
               Json::Value meshValue;
               meshValue["@class"] = "Mesh";
               meshValue["fileName"] = "data/meshes/vis.obj";
               modelValue["mesh"] = meshValue;
               SPtr<Model> aegrumModel = loader.loadModel(sScene, modelValue);

               SPtr<Aegrum> aegrum = std::make_shared<Aegrum>(sScene, aegrumModel, ATTACK_POWER);
               aegrum->setRenderState(LIGHTWORLD_STATE | DARKWORLD_STATE);
               aegrum->setPosition(aegrumPos);
               aegrum->setVelocity(shootVec * aegrumSpeed + velocity);
               sScene->getSceneGraph()->addPhys(aegrum);

               glm::vec3 nVel = glm::normalize(aegrum->getVelocity());
               float angle = glm::acos(glm::dot(nVel, glm::vec3(1.0f, 0.0f, 0.0f)));
               if (nVel.y < 0) {
                  angle *= -1.0f;
               }
               aegrum->setOrientation(glm::angleAxis(angle, glm::vec3(0.0f, 0.0f, 1.0f)));
               sScene->getSceneGraph()->addPhys(aegrum);

               //Move around
               evasiveManuevers(playerPos - position);

            }


            ATTACK_TIME -= dt;
         }*/


      }

   }


   Enemy::tick(dt);
}

int Boss::getAttackPower() {
   return ATTACK_POWER;
}

#define COLLISION_CLASS_NAME Boss
#include "CollisionsBoilerplateCpp.h"