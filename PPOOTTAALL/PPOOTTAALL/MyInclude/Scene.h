#pragma once

#include "Game.h"

class Player;
class Mesh;
class Plane;
class Portal;
class Cube;
class Button;

class Scene {
private:
	bool m_bDragging = false;
	POINT m_tBefPoint = { 0,0 };
	int m_iSceneNum;

public:
	CameraVectors m_tCamera;

private:
	int m_iShoot = 0;
	bool m_bClear = false;

private:
	Portal* m_pPortal[2];
	std::vector<Plane*> m_pFloor;
	std::vector<Plane*> m_pWalls;
	std::vector<Plane*> m_pGlasses;
	std::vector<Plane*> m_pPortalWalls;
	std::vector<Button*> m_pButtons;
	std::vector<Cube*> m_pCubes;

	Player* m_pPlayer;


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
	void mouseActFucn(int key, int state, POINT pt);
	// movesMove
	void moveMouse(POINT pt, bool hideMode = false);
	// mouseWheel
	void scrollMouse(int dir);

public:
	glm::mat4 getPortalView(Portal* from, Portal* dist);
};

