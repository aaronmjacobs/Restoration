#include "GLIncludes.h"
#include "SceneGraph.h"

#include "CollisionsIncludes.h"

const std::string Turris::CLASS_NAME = "Turris";

const int Turris::BASE_HEALTH = 14;
const int Turris::ATTACK_POWER = 4;
float Turris::ATTACK_TIME = 5.0f;

Turris::Turris(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Enemy(scene, model, BASE_HEALTH, ATTACK_POWER, name) {
}

Turris::~Turris() {
}

Json::Value Turris::serialize() const {
   Json::Value root = Enemy::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Turris::tick(const float dt) {
   // TODO AI
   setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));

   if (ATTACK_TIME <= 0) {

      SPtr<Scene> sScene = scene.lock();
      if (sScene) {
         SPtr<Player> player = sScene->getPlayer().lock();
         if (player) {
            glm::vec3 playerPos = player->getPosition();
            glm::vec3 shootVec = glm::normalize(playerPos - position);

            if (glm::length(position - playerPos) < 15.0f) {
               float aegrumCreationDistance = 0.5f;
               float aegrumSpeed = 15.0f;
               glm::vec3 aegrumPos = position + shootVec * aegrumCreationDistance;

               SPtr<Aegrum> aegrum = std::make_shared<Aegrum>(sScene, model);
               aegrum->setRenderState(STENCIL_STATE | LIGHTWORLD_STATE | DARKWORLD_STATE);
               aegrum->setPosition(aegrumPos);
               aegrum->setVelocity(shootVec * aegrumSpeed + velocity);
               sScene->getSceneGraph()->addPhys(aegrum);
            }

         }
      }
      ATTACK_TIME = 5.0f;
   }
   ATTACK_TIME -= dt;

   Enemy::tick(dt);
}

int Turris::getAttackPower() {
   return ATTACK_POWER;
}

#define COLLISION_CLASS_NAME Turris
#include "CollisionsBoilerplateCpp.h"
