#ifndef LVLEDIT_H
#define LVLEDIT_H

#include "InputListener.h"
#include "Types.h"
#include "PhysicalObject.h"

#define TRANSLATE 0
#define SCALE 1
#define ROTATE 2
#define CREATE 3
#define PASTE 4

#define MAIN 0
#define FORE 1
#define BACK 2

#define MAXOBJS 50

class Scene;

class LevelEditor : public InputListener, public TickListener {
private:
   WPtr<Scene> scene;

    bool saved = true, enabled = false, big = false, precision = false, ctrlDown = false, spaceDown = false, list1 = true;
	bool transUp = false, transDown = false, transRight = false, transLeft = false, transBack = false, transFront = false;
	bool transX = false, transY = false, transZ = false;

	int editState = TRANSLATE, stageState = MAIN, keepTransforming = 0, numObjs = 0, copyObjs = 0;

	SPtr<PhysicalObject> currentObj = NULL, placeObj = NULL, currentObjs[MAXOBJS], copyBuf[MAXOBJS];
	glm::vec3 copyObjPos[MAXOBJS], copyAvg;
	double prevPoint[2];
	double rotate = 0.0;

	int listNum = 1;
	std::string objFiles1[10];
	std::string objFiles2[10];
	std::string objFiles3[10];
	std::string *curFileList = objFiles1;
	std::string curObjFile = "data/meshes/block.obj";
	glm::vec3 curTransformVec = glm::vec3(0.0, 0.0, 0.0);
public:
	/**
	 * Makes a level editor with the given string and json file
	 */
	LevelEditor(SPtr<Scene> scene);

	/**
	 * Cleanup
	 */
	~LevelEditor();

	//function for key input
	virtual void onKeyEvent(int key, int action);

	//function for mouse input
	virtual void onMouseButtonEvent(int button, int action);

	virtual void onMouseMotionEvent(double xPos, double yPos);

	virtual void transform(glm::vec3 trans);

	virtual void changeGround(int gound);
	
	virtual void quickSwitch(int key);

	virtual SPtr<PhysicalObject> getCurObj();

	bool isEnabled();

	/**
	* Steps |dt| seconds through time.
	*/
	virtual void tick(const float dt);

	virtual void printVec(glm::vec3 ray);
};

#endif