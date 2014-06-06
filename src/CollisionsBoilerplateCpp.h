#define COLLISION_FUNCTION(OTHER_CLASS) \
void COLLISION_CLASS_NAME::collideWith(OTHER_CLASS &other) { \
   SPtr<Scene> sScene = scene.lock(); \
   if (sScene) { \
      sScene->getCollisionHanlder().handleCollision(*this, other); \
   } \
} \

void COLLISION_CLASS_NAME::collideWith(PhysicalObject &other) {
   other.collideWith(*this);
}

COLLISION_FUNCTION(Aegrum)
COLLISION_FUNCTION(Boss)
COLLISION_FUNCTION(Character)
COLLISION_FUNCTION(Corona)
COLLISION_FUNCTION(Enemy)
COLLISION_FUNCTION(Justitia)
COLLISION_FUNCTION(Magus)
COLLISION_FUNCTION(MovableObject)
COLLISION_FUNCTION(Obex)
COLLISION_FUNCTION(Player)
COLLISION_FUNCTION(Scenery)
COLLISION_FUNCTION(Turris)
COLLISION_FUNCTION(Vagus)
COLLISION_FUNCTION(Vis)