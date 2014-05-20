#include "CameraController.h"

CameraController::CameraController(SPtr<Camera> camera)
: camera(camera), enabled(false) {
}

CameraController::~CameraController() {
}

void CameraController::setEnabled(bool enabled) {
   this->enabled = enabled;
}
