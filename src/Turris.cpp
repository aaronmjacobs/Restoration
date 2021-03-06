#include "GLIncludes.h"
#include "Loader.h"
#include "Particle.h"
#include "SceneGraph.h"

#include "CollisionsIncludes.h"

const std::string Turris::CLASS_NAME = "Turris";

const float Turris::BASE_HEALTH = 30.0f;
const float Turris::HEALTH_REPLACEMENT = 7.0f;
const float Turris::ATTACK_POWER = 7.0f;
const float Turris::ATTACK_DELAY = 1.5f;

Turris::Turris(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
: Enemy(scene, model, BASE_HEALTH, HEALTH_REPLACEMENT, ATTACK_POWER, name) {
   attackTime = 0.0f;
}

Turris::~Turris() {
}

Json::Value Turris::serialize() const {
   Json::Value root = Enemy::serialize();

   root["@class"] = CLASS_NAME;

   return root;
}

void Turris::draw(const RenderData &renderData) {
   // Skip the character draw, so the orientation doesn't change
   MovableObject::draw(renderData);
}

void Turris::tick(const float dt) {
   attackTime += dt;

   if (attackTime > ATTACK_DELAY) {
      attackTime = 0.0f;
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

               if (sScene) {
                  Particle::createEffect(sScene,
                                         getPosition(), // Position
                                         glm::vec3(0.0f),   // Velocity
                                         false,             // Gravity enabled
                                         5.0f,              // Size
                                         5,                // Number of particles
                                         3.0f,              // Duration (seconds)
                                         25.0f,             // Particle spread
                                         false);             // Stencil mode
               }
            }
         }
      }
   }

   Enemy::tick(dt);
}

int Turris::getAttackPower() {
   return ATTACK_POWER;
}

#define COLLISION_CLASS_NAME Turris
#include "CollisionsBoilerplateCpp.h"
