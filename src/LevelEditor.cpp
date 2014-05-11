#include "GLIncludes.h"
#include "LevelEditor.h"
#include "Scene.h"
#include "Camera.h"
#include "FlatSceneGraph.h"

#include "Mesh.h"
#include "Model.h"
#include "Loader.h"
#include "Material.h"
#include "MovableObject.h"

/*
*Todo
*Change Listeners
*Create LE scene
*/
LevelEditor::LevelEditor(SPtr<Scene> scene)
: scene(scene) {
	prevPoint[0] = 0.0;
	prevPoint[1] = 0.0;
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
	if (action == GLFW_PRESS) {
		if (!levelOn()) {
			if (key == GLFW_KEY_GRAVE_ACCENT) {
				on = true;
				printf("LEVEL EDIT MODE ENABLED\n");
			}
			return;
		}
		else if (key == GLFW_KEY_Q) {
			if (saved) {
				on = false;
			}
			else {
				// Ask before doing
				on = false;
			}
		}
		else if (key == GLFW_KEY_UP) {
			transUp = true;
			//keepTransforming++;
			if (editState == TRANSLATE) {
				if (big)
					curTransformVec = glm::vec3(0.0, 0.35, 0.0);
				else
					curTransformVec = glm::vec3(0.0, 0.05, 0.0);
			}
			else if (editState == SCALE) {
				if (big)
					curTransformVec = glm::vec3(1.0, 1.25, 1.0);
				else
					curTransformVec = glm::vec3(1.0, 1.05, 1.0);
			}
		}
		else if (key == GLFW_KEY_DOWN) {
			transDown = true;
			//keepTransforming++;
			if (editState == TRANSLATE) {
				if (big)
					curTransformVec = glm::vec3(0.0, -0.35, 0.0);
				else
					curTransformVec = glm::vec3(0.0, -0.05, 0.0);
			}
			else if (editState == SCALE) {
				if (big)
					curTransformVec = glm::vec3(1.0, 0.75, 1.0);
				else
					curTransformVec = glm::vec3(1.0, 0.95, 1.0);
			}
		}
		else if (key == GLFW_KEY_LEFT) {
			transLeft = true;
			//keepTransforming++;
			if (editState == TRANSLATE) {
				if (big)
					curTransformVec = glm::vec3(-0.35, 0.0, 0.0);
				else
					curTransformVec = glm::vec3(-0.05, 0.0, 0.0);
			}
			else if (editState == SCALE) {
				if (big)
					curTransformVec = glm::vec3(0.75, 1.0, 1.0);
				else
					curTransformVec = glm::vec3(0.95, 1.0, 1.0);
			}
		}
		else if (key == GLFW_KEY_RIGHT) {
			transRight = true;
			//keepTransforming++;
			if (editState == TRANSLATE) {
				if (big)
					curTransformVec = glm::vec3(0.35, 0.0, 0.0);
				else
					curTransformVec = glm::vec3(0.05, 0.0, 0.0);
			}
			else if (editState == SCALE) {
				if (big)
					curTransformVec = glm::vec3(1.25, 1.0, 1.0);
				else
					curTransformVec = glm::vec3(1.05, 1.0, 1.0);
			}
		}
		else if (key == GLFW_KEY_APOSTROPHE) {
			transBack = true;
			//keepTransforming++;
			if (editState == TRANSLATE) {
				if (big)
					curTransformVec = glm::vec3(0.0, 0.0, -0.35);
				else
					curTransformVec = glm::vec3(0.0, 0.0, -0.05);
			}
			else if (editState == SCALE) {
				if (big)
					curTransformVec = glm::vec3(1.0, 1.0, 0.75);
				else
					curTransformVec = glm::vec3(1.0, 1.0, 0.95);
			}
		}
		else if (key == GLFW_KEY_LEFT_BRACKET) {
			transFront = true;
			//keepTransforming++;
			if (editState == TRANSLATE) {
				if (big)
					curTransformVec = glm::vec3(0.0, 0.0, 0.35);
				else
					curTransformVec = glm::vec3(0.0, 0.0, 0.05);
			}
			else if (editState == SCALE) {
				if (big)
					curTransformVec = glm::vec3(1.0, 1.0, 1.25);
				else
					curTransformVec = glm::vec3(1.0, 1.0, 1.05);
			}
		}
		else if (key == GLFW_KEY_P) {
			if (!precision)
				precision = true;
			else
				precision = false;
		}
		else if (key == GLFW_KEY_T) {
			editState = TRANSLATE;
		}
		else if (key == GLFW_KEY_Y) {
			editState = SCALE;
		}
		else if (key == GLFW_KEY_R) {
			editState = ROTATE;
		}
		else if (key == GLFW_KEY_C) {
			editState = CREATE;
		}
		else if (key == GLFW_KEY_F) {
			stageState = FORE;
		}
		else if (key == GLFW_KEY_B) {
			stageState = BACK;
		}
		else if (key == GLFW_KEY_M) {
			stageState = MAIN;
		}
		else if (key == GLFW_KEY_G) {
			if (!big)
				big = true;
			else
				big = false;
		}
		/*else if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) {
			quickSwitch(key);
		}*/
		else if (key == GLFW_KEY_Z) {
			if (currentObj) {
				currentObj->markForRemoval();
				currentObj.reset();
			}
		}
		else if (key == GLFW_KEY_X) {
			currentObj = NULL;
		}
	}
	else if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_UP)
			transUp = false;
		else if (key == GLFW_KEY_DOWN)
			transDown = false;
		else if (key == GLFW_KEY_LEFT)
			transLeft = false;
		else if (key == GLFW_KEY_RIGHT)
			transRight = false;
		else if (key == GLFW_KEY_APOSTROPHE)
			transBack = false;
		else if (key == GLFW_KEY_LEFT_BRACKET)
			transFront = false;
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
	glm::mat4 proj, view;
	glm::vec3 mousePos, mouseRay, near, far, newObjPos;
	glm::vec4 viewP;
	SPtr<SceneGraph> graph;
	SPtr<PhysicalObject> tempObj;

	if (!levelOn()) {
		return;
	}
	else if (action == GLFW_PRESS) {
		SPtr<Scene> s = scene.lock();
		if (!s) {
			printf("bad scene\n");
			return;
		}
		graph = s->getSceneGraph();

		if (editState == CREATE) {
			//place current object type specified with #0-9
			std::cout << "Creating new object" << std::endl;

			SPtr<Mesh> mesh = std::make_shared<Mesh>("data/meshes/cello_and_stand.obj");
			SPtr<Loader> loader = Loader::getInstance();
			SPtr<Material> material2 = loader->loadMaterial(s, "otherMaterial");
			SPtr<Model> model = std::make_shared<Model>(material2, mesh);

			SPtr<MovableObject> newObj = std::make_shared<MovableObject>(s, model);

			//tempObj = SPtr<PhysicalObject>(placeObj);
			glm::vec3 pos(0.0f, 0.0f, -3.0f);
			SPtr<Camera> camera = s->getCamera().lock();

			if (camera) {
				pos += camera->getPosition();
			}

			if (stageState == MAIN) {
				pos.z = 0.0;
			}
			else if (stageState == FORE) {
				if (pos.z < 0.0)
					pos.z = -pos.z;
			}
			else if (stageState == BACK) {
				if (pos.z > 0.0)
					pos.z = -pos.z;
			}

			newObj->setPosition(pos);
			currentObj = newObj;
			s->getSceneGraph()->addPhys(newObj);
			editState = TRANSLATE;
			//}
			//else {
			//	printf("no specified object to place");
			//}
		}
		else {
			tempObj = graph->mouseCollides(prevPoint[0], prevPoint[1]);
			if (tempObj != NULL) {
				currentObj = tempObj;
			}
			//printf("%f %f\n", prevPoint[0], prevPoint[1]);
		}
	}
}

/*
 * Transforms highlighted object with current transform
 */
void LevelEditor::onMouseMotionEvent(double xPos, double yPos) {
	prevPoint[0] = xPos;
	prevPoint[1] = yPos;

	if (!levelOn()) {
		return;
	}
	else if (editState == TRANSLATE) {

	}
	else if (editState == SCALE) {

	}
	else if (editState == ROTATE) {

	}
}

/*
 * Check current objects location and scale values
 * add stuff to them depending on mode
 */
void LevelEditor::transform(glm::vec3 trans) {
	if (!levelOn()) {
		return;
	}
	else if (!currentObj) {
		printf("no current object selected\n");
	}
	else {
		if (editState == TRANSLATE) {
			currentObj->translateBy(trans);
		}
		else if (editState == SCALE) {
			currentObj->scaleBy(trans);
		}
		else if (editState == ROTATE) {

		}
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

SPtr<PhysicalObject> LevelEditor::getCurObj() {
	return currentObj;
}

void LevelEditor::tick(const float dt) {
	glm::vec3 v = curTransformVec;
	//printf("v: (x) %f.2 (y) %f.2 (z) %f.2", v.x, v.y, v.z);
	if ((v.x == 1.0 && v.y == 1.0) || (v.x == 0.0 && v.y == 0.0)) {
		//printf("hello?\n");
		if ((((editState == TRANSLATE && v.z > 0.0 && v.x == 0.0 && v.y == 0.0) || (editState == SCALE && v.z > 1.0)) && transFront) ||
			(((editState == TRANSLATE && v.z < 0.0) || (editState == SCALE && v.z < 1.0)) && transBack)) {
			transform(v);
		}
	}
	else if ((v.z == 1.0 && v.y == 1.0) || (v.z == 0.0 && v.y == 0.0)) {
		if ((((editState == TRANSLATE && v.x > 0.0) || (editState == SCALE && v.x > 1.0)) && transRight) ||
			(((editState == TRANSLATE && v.x < 0.0) || (editState == SCALE && v.x < 1.0)) && transLeft)) {
			transform(v);
		}
	}
	else if ((v.x == 1.0 && v.z == 1.0) || (v.x == 0.0 && v.z == 0.0)) {
		if ((((editState == TRANSLATE && v.y > 0.0) || (editState == SCALE && v.y > 1.0)) && transUp) ||
			(((editState == TRANSLATE && v.y < 0.0) || (editState == SCALE && v.y < 1.0)) && transDown)) {
			transform(v);
		}
	}
	if (precision) {
		if ((v.x == 1.0 && v.y == 1.0) || (v.x == 0.0 && v.y == 0.0)) {
			if ((editState == TRANSLATE && v.z > 0.0) || (editState == SCALE && v.z > 1.0))
				transFront = false;
			else
				transBack = false;
		}
		else if ((v.z == 1.0 && v.y == 1.0) || (v.z == 0.0 && v.y == 0.0)) {
			if ((editState == TRANSLATE && v.x > 0.0) || (editState == SCALE && v.x > 1.0))
				transRight = false;
			else
				transLeft = false;
		}
		else if ((v.x == 1.0 && v.z == 1.0) || (v.x == 0.0 && v.z == 0.0)) {
			if ((editState == TRANSLATE && v.y > 0.0) || (editState == SCALE && v.y > 1.0))
				transUp = false;
			else
				transDown = false;
		}
	}
}