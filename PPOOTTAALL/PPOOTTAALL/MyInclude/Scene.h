#pragma once

#include "Game.h"

class Player;
class Mesh;
class Plane;
class Portal;
class Cube;

class Scene {
private:
	bool m_bDragging = false;
	POINT m_tBefPoint = { 0,0 };
	int m_iSceneNum;

public:
	CameraVectors m_tCamera;

private:
	Plane* m_pFloor;
	std::vector<Plane*> m_pWalls;
	Portal* m_pPortal[2];
	std::vector<Plane*> m_pPortalWalls;

	Player* m_pPlayer;

	Cube* m_pCube[2];

public:
	Scene() = delete;
	Scene(int sceneNum, CameraVectors& cam);
	~Scene();

public:
	void input();
	void update(float frameTime);
	void draw(unsigned int shaderNum, int textureBind, bool main = false);

	void drawPortal(unsigned int shaderNum, int textureBind);
	
public:
	// mouseAct
	void activeDragging(bool active, POINT pt);
	// movesMove
	void moveMouse(POINT pt, bool hideMode = false);
	// mouseWheel
	void scrollMouse(int dir);

public:
	glm::mat4 getPortalView(Portal* from, Portal* dist);
};

