#ifndef LVLEDIT_H
#define LVLEDIT_H

#include "InputListener.h"
#include "Types.h"
#include "PhysicalObject.h"

#define TRANSLATE 0
#define SCALE 1
#define ROTATE 2
#define CREATE 3

#define MAIN 0
#define FORE 1
#define BACK 2

class Scene;

class LevelEditor : public InputListener, public TickListener {
private:
   WPtr<Scene> scene;

	bool saved = true, on = false, big = false;

	int editState = TRANSLATE, stageState = MAIN, keepTransforming = 0;

	SPtr<PhysicalObject> currentObj = NULL, placeObj = NULL;

	double prevPoint[2];

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

	bool levelOn();

	/**
	* Steps |dt| seconds through time.
	*/
	virtual void tick(const float dt);
};

#endif