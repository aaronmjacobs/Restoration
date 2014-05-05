#ifndef LVLEDIT_H
#define LVLEDIT_H

#include "InputListener.h"
#include "Types.h"

class Scene;

class LevelEditor : public InputListener {
private:
   WPtr<Scene> scene;

	//Transformation Modes
	bool transMode = true, rotMode = false, scaleMode = false, createMode = false;
	//Three types of areas to build on
	bool foreground = false, background = false, mainground = true;

	bool saved = true, on = false;

	double prevPoint[2] = { 0.0, 0.0 };

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

	virtual void transform(double x, double y);

	virtual void changeGround(int gound);
	
	virtual void quickSwitch(int key);

	bool levelOn();
};

#endif