#include "CameraController.h"

CameraController::CameraController(SPtr<Camera> camera)
: camera(camera) {
   fade = 1.0f;
}

CameraController::~CameraController() {
}

void CameraController::tick(const float dt) {
   //
}

void CameraController::onKeyEvent(int key, int action) {
   //
}

void CameraController::onMouseButtonEvent(int button, int action) {
   //
}

void CameraController::onMouseMotionEvent(double xPos, double yPos) {
   //
}