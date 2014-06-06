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
#include "Scenery.h"
#include "IOUtils.h"

/*
*Todo
*Change Listeners
*Create LE scene
*/
LevelEditor::LevelEditor(SPtr<Scene> scene)
: scene(scene) {
	prevPoint[0] = 0.0;
	prevPoint[1] = 0.0;
	objFiles1[0] = "data/meshes/block.obj";
	objFiles1[1] = "data/meshes/aquaduct.obj";
	objFiles1[2] = "data/meshes/archGem_goal.obj";
	objFiles1[3] = "data/meshes/back_inside.obj";
	objFiles1[4] = "data/meshes/back_insideEnd.obj";
	objFiles1[5] = "data/meshes/block_long.obj";
	objFiles1[6] = "data/meshes/pillar.obj";
	objFiles1[7] = "data/meshes/sand_background.obj";
	objFiles1[8] = "data/meshes/structure_temple.obj";
	objFiles1[9] = "data/meshes/block.obj";
	objFiles2[0] = "data/meshes/groundPath.obj";
	objFiles2[1] = "data/meshes/groundPath.obj";
	objFiles2[2] = "data/meshes/frontPath1.obj";
	objFiles2[3] = "data/meshes/frontPath2.obj";
	objFiles2[4] = "data/meshes/frontPath3.obj";
	objFiles2[5] = "data/meshes/backPath1.obj";
	objFiles2[6] = "data/meshes/backPath2.obj";
	objFiles2[7] = "data/meshes/backPath3.obj";
	objFiles2[8] = "data/meshes/sand_background.obj";
	objFiles2[9] = "data/meshes/sand_background.obj";
	objFiles3[0] = "data/meshes/seraCrystal.obj";
	objFiles3[1] = "data/meshes/crate.obj";
	objFiles3[2] = "data/meshes/Pot.obj";
	objFiles3[3] = "data/meshes/spikes.obj";
	objFiles3[4] = "data/meshes/rock_1.obj";
	objFiles3[5] = "data/meshes/rock_2.obj";
	objFiles3[6] = "data/meshes/rock_3.obj";
	objFiles3[7] = "data/meshes/rock_4.obj";
	objFiles3[8] = "data/meshes/tree_dark.obj";
	objFiles3[9] = "data/meshes/block_long.obj";
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
	char yes = 'n';
	if (action == GLFW_PRESS) {
      if (key == GLFW_KEY_GRAVE_ACCENT) {
         enabled = !enabled;

		 if (!enabled) {
			 for (int i = 0; i < numObjs; i++) {
				 currentObjs[i]->getModel()->getMaterial()->setSelected(false);
			 }
			 numObjs = 0;
		 }

         SPtr<Scene> sScene = scene.lock();
         if (sScene) {
            sScene->setEditMode(enabled);
         }

         if (!isEnabled()) {
            return;
         }
      }
		else if (key == GLFW_KEY_Q) {
			if (saved) {
				enabled = false;
			}
			else {
				// Ask before doing
				printf("Quit without saving? (y/n) ");
				scanf("%c", &yes);
				if (yes == 'y') {
					enabled = false;
					yes = 'n';
				}
			}
		}
		else if (key == GLFW_KEY_UP) {
			transUp = true;
			//keepTransforming++;
			if (editState == TRANSLATE) {
				if (big)
					curTransformVec = glm::vec3(0.0, 0.50, 0.0);
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
					curTransformVec = glm::vec3(0.0, -0.50, 0.0);
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
					curTransformVec = glm::vec3(-0.50, 0.0, 0.0);
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
					curTransformVec = glm::vec3(0.50, 0.0, 0.0);
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
					curTransformVec = glm::vec3(0.0, 0.0, -0.50);
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
					curTransformVec = glm::vec3(0.0, 0.0, 0.50);
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
			if (ctrlDown) {
				editState = PASTE;
			}
			else {
				if (!precision)
					precision = true;
				else
					precision = false;
			}
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
			if (ctrlDown) {
				//Copy curObjs into copy buffer
				copyAvg = glm::vec3(0.0, 0.0, 0.0);
				if (numObjs) {
					for (int i = 0; i < numObjs; i++) {
						copyBuf[i] = currentObjs[i];
						copyObjPos[i] = currentObjs[i]->getPosition();
						copyAvg += copyObjPos[i];
					}
					copyObjs = numObjs;
					copyAvg /= copyObjs;
					copyAvg.z = 0.0;
				}
				else
					std::cout << "no objects to be copied" << std::endl;
			}
			else
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
		else if (key == GLFW_KEY_H) {
			printf("hey\n");
			for (int i = 0; i < numObjs; i++) {
				currentObjs[i]->scaleBy(glm::vec3(-1.0, 1.0, 1.0));
			}
			/*if (currentObj && editState == SCALE) {
				printf("hi\n");
				currentObj->scaleBy(glm::vec3(-1.0, 1.0, 1.0));
				printVec(currentObj->getScale());
			}*/
		}
		/*else if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) {
			quickSwitch(key);
		}*/
		else if (key == GLFW_KEY_Z) {
			for (int i = 0; i < numObjs; i++) {
				currentObjs[i]->markForRemoval();
				currentObjs[i].reset();
			}
			numObjs = 0;
		}
		else if (key == GLFW_KEY_X) {
			for (int i = 0; i < numObjs; i++) {
				currentObjs[i]->getModel()->getMaterial()->setSelected(false);
			}
			numObjs = 0;
		}
		else if (key == GLFW_KEY_PERIOD) {
			//save here
			//somewhere in scenes maybe?

			std::string fileName;
			std::cout << "Enter file name: ";
			std::cin >> fileName;
			SPtr<Scene> s = scene.lock();
			if (s) {
				IOUtils::save(*s, fileName);
			}

			saved = true;
		}
		else if (key == GLFW_KEY_L) {
			//load here
		}
		else if (key == GLFW_KEY_LEFT_CONTROL) {
			ctrlDown = true;
		}
		else if (key == GLFW_KEY_SPACE) {
			spaceDown = true;
		}
		//OBJ FILE STUFF
		else if (key == GLFW_KEY_0)
			curObjFile = curFileList[0];
		else if (key == GLFW_KEY_1)
			curObjFile = curFileList[1];
		else if (key == GLFW_KEY_2)
			curObjFile = curFileList[2];
		else if (key == GLFW_KEY_3)
			curObjFile = curFileList[3];
		else if (key == GLFW_KEY_4)
			curObjFile = curFileList[4];
		else if (key == GLFW_KEY_5)
			curObjFile = curFileList[5];
		else if (key == GLFW_KEY_6)
			curObjFile = curFileList[6];
		else if (key == GLFW_KEY_7)
			curObjFile = curFileList[7];
		else if (key == GLFW_KEY_8)
			curObjFile = curFileList[8];
		else if (key == GLFW_KEY_9)
			curObjFile = curFileList[9];
		else if (key == GLFW_KEY_EQUAL) {
			if (listNum == 1) {
				curFileList = objFiles2;
				listNum++;
			}
			else if (listNum == 2) {
				curFileList = objFiles3;
				listNum++;
			}
			else if (listNum == 3) {
				curFileList = objFiles1;
				listNum = 1;
			}
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
		else if (key == GLFW_KEY_LEFT_CONTROL) {
			ctrlDown = false;
		}
		else if (key == GLFW_KEY_SPACE) {
			spaceDown = false;
		}
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
	SPtr<Scenery> newObj;
	bool unselected = false;

	if (!isEnabled() || spaceDown) {
		return;
	}
	else if (action == GLFW_PRESS) {
		SPtr<Scene> s = scene.lock();
		if (!s) {
			printf("bad scene\n");
			return;
		}
		SPtr<Camera> camera = s->getCamera().lock();
		if (!camera) {
			return;
		}
		graph = s->getSceneGraph();

		glm::vec3 pos(0.0f, 0.0f, -3.0f);
		pos += camera->getPosition();

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

		if (editState == CREATE) {
			saved = false;
			//place current object type specified with #0-9
			std::cout << "Creating new object" << std::endl;

			SPtr<Mesh> mesh = std::make_shared<Mesh>(curObjFile);
			Loader& loader = Loader::getInstance();
			//printf("a\n");
			SPtr<Material> material2 = loader.loadMaterial(s, "otherMaterial");
			//printf("b\n");
			SPtr<Model> model = std::make_shared<Model>(material2, mesh);
			//printf("c\n");

			newObj = std::make_shared<Scenery>(s, model);

			//tempObj = SPtr<PhysicalObject>(placeObj);

			newObj->setPosition(pos);
			//newObj->rotateBy(glm::vec3(rotate, 0.0, 0.0));
			s->getSceneGraph()->addPhys(newObj);

			//numObjs = 0;
			if (numObjs < MAXOBJS) {
				currentObjs[numObjs] = newObj;
				currentObjs[numObjs++]->getModel()->getMaterial()->setSelected(true);
			}
			else
				std::cout << "Too many objects in buffer" << std::endl;

			if (!ctrlDown)
				editState = TRANSLATE;
			//}
			//else {
			//	printf("no specified object to place");
			//}
		}
		//MAKES A DIRECT COPY OF THE OBJECT(S), IF YOU
		//CHANGE MODEL OR MATERIAL OF ONE, IT CHANGES
		//THE OTHER
		else if (editState == PASTE) {
			for (int i = 0; i < copyObjs; i++) {
				newObj = std::make_shared<Scenery>(s, copyBuf[i]->getModel());
				currentObjs[i]->getModel()->getMaterial()->setSelected(false);
				newObj->getModel()->getMaterial()->setSelected(true);
				newObj->setPosition(glm::vec3((copyObjPos[i].x - copyAvg.x) + camera->getPosition().x, 
											  (copyObjPos[i].y - copyAvg.y) + camera->getPosition().y, copyObjPos[i].z));
				newObj->setScale(currentObjs[i]->getScale());
				s->getSceneGraph()->addPhys(newObj);
				currentObjs[i] = newObj;
			}
			editState = TRANSLATE;
		}
		else {
			tempObj = graph->mouseCollides(prevPoint[0], prevPoint[1]);
			if (tempObj) {
				if (!ctrlDown) {
					for (int i = 0; i < numObjs; i++) {
						currentObjs[i]->getModel()->getMaterial()->setSelected(false);
					}
					numObjs = 0;
				}

				for (int i = 0; i < numObjs; i++) {
					if (unselected)
						currentObjs[i - 1] = currentObjs[i];
					else if (tempObj == currentObjs[i]) {
						unselected = true;
						currentObjs[i]->getModel()->getMaterial()->setSelected(false);
					}
				}

				if (unselected) {
					numObjs--;
					unselected = false;
				}
				else if (numObjs < MAXOBJS) {
					currentObjs[numObjs] = tempObj;
					currentObjs[numObjs++]->getModel()->getMaterial()->setSelected(true);
				}
				else
					std::cout << "Too many objects in buffer" << std::endl;
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

	if (!isEnabled() || spaceDown) {
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
	if (!isEnabled()) {
		return;
	}
	else if (numObjs == 0) {
		printf("no current object selected\n");
	}
	else {
		saved = false;
		if (editState == TRANSLATE) {
			for (int i = 0; i < numObjs; i++) {
				currentObjs[i]->translateBy(trans);
			}
		}
		else if (editState == SCALE) {
			for (int i = 0; i < numObjs; i++) {
				currentObjs[i]->scaleBy(trans);
			}
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

bool LevelEditor::isEnabled() {
	return enabled;
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
void LevelEditor::printVec(glm::vec3 ray) {
	std::cout << "x : " << ray.x << " y: " << ray.y << " z: " << ray.z << std::endl;
}