#include "GLIncludes.h"
#include "LevelEditor.h"
#include "Scene.h"

/*
*Todo
*Change Listeners
*Create LE scene
*/
LevelEditor::LevelEditor(SPtr<Scene> scene)
: scene(scene) {
}

/*
 *Todo
 *Change Listeners
 *Delete Stuff
 */
LevelEditor::~LevelEditor() {
}

/*
 * # 0 - 9 Specify objects
 * 't' translate, 's' scale, 'r' rotate
 * translate automatic
 * wasd for key transforms until mouse incorporated
 * 'f' foreground, 'b' background, 'm' mainground
 * mainground automatic
 * arrow keys to quick switch objects
 */
void LevelEditor::onKeyEvent(int key, int action) {
	if (!levelOn()) {
		if (key == GLFW_KEY_GRAVE_ACCENT) {
			on = true;
		}
		return;
	}
	else if (key == GLFW_KEY_ESCAPE) {
		if (saved) {
			on = false;
		}
		else {
			// Ask before doing
			on = false;
		}
	}
	else if (key == GLFW_KEY_W) {
		transform(0.0, 0.1);
	}
	else if (key == GLFW_KEY_S) {
		transform(0.0, -0.1);
	}
	else if (key == GLFW_KEY_A) {
		transform(-0.1, 0.0);
	}
	else if (key == GLFW_KEY_D) {
		transform(0.1, 0.0);
	}
	else if (key == GLFW_KEY_T) {
		transMode = true;
		rotMode = scaleMode = createMode = false;
	}
	else if (key == GLFW_KEY_S) {
		scaleMode = true;
		rotMode = transMode = createMode = false;
	}
	else if (key == GLFW_KEY_R) {
		rotMode = true;
		transMode = scaleMode = createMode = false;
	}
	else if (key == GLFW_KEY_C) {
		createMode = true;
		transMode = scaleMode = rotMode = false;
	}
	else if (key == GLFW_KEY_F) {
		foreground = true;
		background = mainground = false;
	}
	else if (key == GLFW_KEY_B) {
		background = true;
		foreground = mainground = false;
	}
	else if (key == GLFW_KEY_M) {
		mainground = true;
		background = foreground = false;
	}
	else if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) {
		quickSwitch(key);
	}
}

//function for mouse input
/*
 * Project camera to mouse and on to find first object
 * Highlight object => curObj
 * when unclicked: unhighlight object => curObj = null
 * ^- unless selected via quickswitch
 */
void LevelEditor::onMouseButtonEvent(int button, int action) {
	if (!levelOn()) {
		return;
	}
	else if (createMode) {
		//place current object type specified with #0-9
	}
	else {
		//find object
	}
}

/*
 * Transforms highlighted object with current transform
 */
void LevelEditor::onMouseMotionEvent(double xPos, double yPos) {
	if (!levelOn()) {
		return;
	}
	else if (transMode) {

	}
	else if (scaleMode) {

	}
	else if (rotMode) {

	}
}

/*
 * Check current objects location and scale values
 * add stuff to them depending on mode
 */
void LevelEditor::transform(double x, double y) {
	if (!levelOn()) {
		return;
	}
	else if (transMode) {

	}
	else if (scaleMode) {

	}
	else if (rotMode) {

	}
}

/*
 * Yeah
 */
void LevelEditor::changeGround(int ground) {

}

void LevelEditor::quickSwitch(int arrow) {
	
}

bool LevelEditor::levelOn() {
	return on;
}