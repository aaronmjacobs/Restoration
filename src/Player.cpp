#include "Camera.h"
#include "GLIncludes.h"
#include "Loader.h"
#include "SceneGraph.h"

#include "CollisionsIncludes.h"

const std::string Player::CLASS_NAME = "Player";

const int Player::BASE_HEALTH = 10;
const float Player::WALK_SPEED = 5.0f;
const float Player::JUMP_FORCE = 520.0f;
float Player::INVINC_FRAMES = 0.0f;

Player::Player(SPtr<Scene> scene, SPtr<Model> model, const std::string &name)
   : Character(scene, model, BASE_HEALTH, name) {
   wantsToGoLeft = wantsToGoRight = wantsToJump = wantsToAttack = false;
   lastMouseX = lastMouseY = 0.0f;
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
   SPtr<Scene> sScene = scene.lock();
   if (!sScene || sScene->isInEditMode()) {
      return;
   }

   if (action == GLFW_PRESS) {
      SPtr<Camera> camera = sScene->getCamera().lock();
      if (!camera) {
         return;
      }
      glm::mat4 proj = camera->getProjectionMatrix();
      glm::mat4 view = camera->getViewMatrix();
      glm::vec4 viewP = glm::vec4(0, 0, camera->getWindowWidth(), camera->getWindowHeight());
      glm::vec3 mousePos = glm::vec3(lastMouseX, camera->getWindowHeight() - lastMouseY, 0.0);

      glm::vec3 near = glm::unProject(mousePos, view, proj, viewP);
      mousePos.z = 1.0;
      glm::vec3 far = glm::unProject(mousePos, view, proj, viewP);

      glm::vec3 mouseRay = glm::normalize(far - near);
      glm::vec3 toPlayer = glm::normalize(position - camera->getPosition());
      glm::vec3 playerToMouse = glm::normalize(glm::vec3(mouseRay.x - toPlayer.x, mouseRay.y - toPlayer.y, 0.0f));

      float justitiaCreationDistance = 0.5f;
      float justitiaSpeed = 15.0f;
      glm::vec3 justitiaPos = position + playerToMouse * justitiaCreationDistance;

      Loader &loader = Loader::getInstance();
      Json::Value modelValue;
      modelValue["@class"] = "Model";
      modelValue["material"] = "justitia";
      Json::Value meshValue;
      meshValue["@class"] = "Mesh";
      meshValue["fileName"] = "data/meshes/vis.obj";
      modelValue["mesh"] = meshValue;
      SPtr<Model> justitiaModel = loader.loadModel(sScene, modelValue);

      SPtr<Justitia> justitia = std::make_shared<Justitia>(sScene, justitiaModel);
      justitia->setRenderState(STENCIL_STATE | LIGHTWORLD_STATE | DARKWORLD_STATE);
      justitia->setPosition(justitiaPos);
      justitia->setVelocity(playerToMouse * justitiaSpeed + velocity);

      glm::vec3 nVel = glm::normalize(justitia->getVelocity());
      float angle = glm::acos(glm::dot(nVel, glm::vec3(1.0f, 0.0f, 0.0f)));
      if (nVel.y < 0) {
         angle *= -1.0f;
      }
      justitia->setOrientation(glm::angleAxis(angle, glm::vec3(0.0f, 0.0f, 1.0f)));
      sScene->getSceneGraph()->addPhys(justitia);

      SPtr<Scene> sScene = scene.lock();
      if (sScene) {
         SPtr<Audio> audio = sScene->getAudio();

         audio->signalSound("pew.ogg");
      }
   }
}

void Player::onMouseMotionEvent(double xPos, double yPos) {
   lastMouseX = xPos;
   lastMouseY = yPos;
}

bool playedIsDead = false;

void Player::tick(const float dt) {

   // Kinetic friction
   if (onGround) {
      velocity.x *= 0.85f;
   }

   // Air resistance
   velocity.x *= 0.95f;

   // Static friction
   if (glm::abs(velocity.x) < 0.05f) {
      velocity.x = 0.0f;
   }

   if (wantsToGoLeft && velocity.x > -WALK_SPEED) {
      velocity.x = -WALK_SPEED;
   }
   if (wantsToGoRight && velocity.x < WALK_SPEED) {
      velocity.x = WALK_SPEED;
   }

   static int jumpIndex = 0;
   if (wantsToJump && onGround) {
      onGround = false;
      velocity += glm::vec3(0.0f, JUMP_FORCE, 0.0f) * dt;

      SPtr<Scene> sScene = scene.lock();
      if (sScene) {
         SPtr<Audio> audio = sScene->getAudio();

         if (jumpIndex == 0) {
            audio->signalSound("jumpGrunt1.wav");
         } else if (jumpIndex == 1) {
            audio->signalSound("jumpGrunt2.wav");
         } else if (jumpIndex == 2) {
            audio->signalSound("jumpGrunt3.wav");
         }

         jumpIndex = (jumpIndex + 1) % 3;
      }
   }

   if (!isAlive() && !playedIsDead) {
      SPtr<Scene> sScene = scene.lock();
      if (sScene) {
         SPtr<Audio> audio = sScene->getAudio();

         audio->signalSound("dead.ogg");
      }
   }

   if (wantsToAttack) {
      // TODO Handle attack logic
   }

   //Invincibility frames
   if (INVINC_FRAMES > 0.0f) {
      INVINC_FRAMES -= dt;
   }

   Character::tick(dt);
}

float Player::getInvFrames() {
   return INVINC_FRAMES;
}

void Player::setInvFrames(float time) {
   INVINC_FRAMES = time;
}

void Player::setHealth(int health) {
   if (INVINC_FRAMES <= 0.0f) {
      if (health != getHealth()) {
         printf("Health: %d\n", health);
      }
      Character::setHealth(health);
   }
}

#define COLLISION_CLASS_NAME Player
#include "CollisionsBoilerplateCpp.h"
