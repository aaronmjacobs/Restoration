#include "FollowGeometry.h"
#include "Enemy.h"
#include "Scene.h"
#include "Player.h"

const std::string FollowGeometry::CLASS_NAME = "FollowGeometry";

FollowGeometry::FollowGeometry(SPtr<Scene> scene, SPtr<Model> model, SPtr<SceneObject> target, const std::string &name)
: Geometry(scene, model, name), target(target) {
   ASSERT(!target->getName().empty(), "Target can not have empty name");
}

FollowGeometry::~FollowGeometry() {
}

Json::Value FollowGeometry::serialize() const {
   Json::Value root = Geometry::serialize();

   // Class name
   root["@class"] = CLASS_NAME;

   SPtr<SceneObject> sTarget = target.lock();
   if (sTarget) {
      root["target"] = sTarget->getName();
   } else {
      root["target"] = Json::nullValue;
   }

   return root;
}

void FollowGeometry::draw(const RenderData &renderData) {
   SPtr<SceneObject> sTarget = target.lock();
   if (sTarget) {
      setPosition(sTarget->getPosition());
   }

   setScale(glm::vec3(0.0f));
   if (Enemy::maxEnemies > 0) {
      float enemyPercent = 1.0f - (float)Enemy::numEnemies / Enemy::maxEnemies;
      SPtr<Scene> sScene = scene.lock();
      if (!sScene) {
         return;
      }
      SPtr<Player> player = sScene->getPlayer().lock();
      if (!player) {
         return;
      }
      float playerHealthPercent = (float)player->getHealth() / Player::BASE_HEALTH;
      setScale(glm::vec3(1.0f + enemyPercent * 10.0f * playerHealthPercent));
   }

   Geometry::draw(renderData);
}

void FollowGeometry::tick(const float dt) {
   Geometry::tick(dt);
   SPtr<SceneObject> sTarget = target.lock();
   if (sTarget) {
      setPosition(sTarget->getPosition());
   }
}
