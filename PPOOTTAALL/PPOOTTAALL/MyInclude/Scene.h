#pragma once

#include "Game.h"

class Player;
class Mesh;
class Plane;
class RotatingCube;

class Scene {
private:
	bool m_bDragging = false;
	POINT m_tBefPoint = { 0,0 };
	int m_iSceneNum;

public:
	CameraVectors m_tCamera;

private:
	Plane* m_pPlane;

	Player* m_pPlayer;

public:
	Scene() = delete;
	Scene(int sceneNum, CameraVectors& cam);
	~Scene();

public:
	void input();
	void update(float frameTime);
	void draw(unsigned int shaderNum, int textureBind);
	
public:
	// mouseAct
	void activeDragging(bool active, POINT pt);
	// movesMove
	void moveMouse(POINT pt);
	// mouseWheel
	void scrollMouse(int dir);

public:

};
