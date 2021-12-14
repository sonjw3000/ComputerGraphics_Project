#include "Core.h"
#include "ShaderProgram.h"
#include "Scene.h"
#include "Plane.h"
#include "Cube.h"
#include "Player.h"
#include "Portal.h"
#include "CollisionCheck.h"
#include "Button.h"
#include <gl/glm/gtx/intersect.hpp>

inline void printVector(glm::vec3 vec)
{
	printf("%.2f, %.2f, %.2f\n", vec.x, vec.y, vec.z);
}

inline bool isSameFloat(float a, float b)
{
	return abs(a - b) < 0.01f;
}

Scene::Scene(int sceneNum, CameraVectors& cam) :
	m_pPortal{ nullptr, nullptr },
	m_iSceneNum(sceneNum) 
{
	m_pFloor.push_back(new Plane("Objs/Plane.obj", glm::vec3(21.0f, 0.1f, 21.0f), glm::vec3(0.0f), glm::vec3(0.0f), "Texture/bg.png"));
	m_pPlayer = new Player(0.4f, glm::vec3(0.0f));

	// right
	m_pWalls.push_back(
		new Plane("Objs/Plane.obj",
			glm::vec3(11.0f, 0.0f, 22.0f),
			glm::vec3(0.0f, 0.0f, -90.0f),
			glm::vec3(-10.0f, 5.0f, 0.0f),
			"Texture/wall.png"));

	// left
	m_pWalls.push_back(
		new Plane("Objs/Plane.obj",
			glm::vec3(11.0f, 0.0f, 22.0f),
			glm::vec3(0.0f, 0.0f, 90.0f),
			glm::vec3(10.0f, 5.0f, 0.0f),
			"Texture/wall.png"));

	// back
	m_pWalls.push_back(
		new Plane("Objs/Plane.obj",
			glm::vec3(22.0f, 0.0f, 11.0f),
			glm::vec3(90.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 5.0f, -10.0f),
			"Texture/wall.png"));

	// front
	m_pWalls.push_back(
		new Plane("Objs/Plane.obj",
			glm::vec3(22.0f, 0.0f, 11.0f),
			glm::vec3(-90.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 5.0f, 10.0f),
			"Texture/wall.png"));

	switch (sceneNum) {
	case 0:
		// player
		m_pPlayer->setTranslate(glm::vec3(9.0f, 1.0f, -9.0f));

		// cube
		m_pCubes.push_back(
			new Cube("Objs/PortalCube.obj",
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(0.0f), glm::vec3(-9.0f, 5.0f, 7.0f),
				"Texture/PortalCube.jpg"));
		m_pCubes.push_back(
			new Cube("Objs/PortalCube.obj",
				glm::vec3(0.5f),
				glm::vec3(0.0f),
				glm::vec3(5.0f, 8.0f, 5.0f),
				"Texture/PortalCube.jpg"));
		// portal walls
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(1.0f, 0.0f, 2.0f),
				glm::vec3(-90.0f, 0.0f, 0.0f),
				glm::vec3(4.5f, 1.0f, 9.99f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(1.0f, 0.0f, 2.0f),
				glm::vec3(-90.0f, 0.0f, 0.0f),
				glm::vec3(5.5f, 1.0f, 9.99f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, -90.0f),
				glm::vec3(-9.99f, 1.0f, 1.5f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, -90.0f),
				glm::vec3(-9.99f, 1.0f, 0.5f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, -90.0f),
				glm::vec3(-9.99f, 6.0f, 7.5f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, -90.0f),
				glm::vec3(-9.99f, 6.0f, 6.5f),
				"Texture/realwhite.png"));

		// wall
		m_pButtons.push_back(
			new Button(2.0f, 
				glm::vec3(9.0f, 0.01f, -9.0f)));

		// transparent wall
		m_pFloor.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(2.0f, 0.1f, 2.0f),
				glm::vec3(0.0f),
				glm::vec3(-9.0f, 4.99f, 7.0f),
				"Texture/alphablue.png"));
		m_pGlasses.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(0.1f, 1.0f, 20.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.f, 0.0f),
				"Texture/alphablue.png"));
		m_pGlasses.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(0.1f, 10.0f, 20.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 6.f, 0.0f),
				"Texture/alphablue.png"));

		//m_pPortal[0] = new Portal(1.0f, 2, glm::vec3(5.0f, 1.0f, 10.0f));
		//m_pPortal[1] = new Portal(1.0f, 1, glm::vec3(-10.0f, 1.0f, 1.0f));



		//m_pGlasses.push_back(
		//	new Plane("Objs/Cube.obj",
		//		glm::vec3(10.0f, 0.1f, 20.0f),
		//		glm::vec3(0.0f, 0.0f, 90.0f),
		//		glm::vec3(0.0f, 3.0f, 0.0f),
		//		"Texture/alphablue.png"));

		break;
	case 1:
		m_pPlayer->setTranslate(glm::vec3(-9.0f, 1.0f, -9.0f));
		m_pCubes.push_back(
			new Cube("Objs/PortalCube.obj",
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(0.0f),
				glm::vec3(-9.0f, 8.0f, 7.0f),
				"Texture/PortalCube.jpg"));

		// portal walls
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, -90.0f),
				glm::vec3(-9.99f, 1.0f, 1.5f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, -90.0f),
				glm::vec3(-9.99f, 1.0f, 0.5f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, -90.0f),
				glm::vec3(-9.99f, 9.0f, 7.5f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, -90.0f),
				glm::vec3(-9.99f, 9.0f, 6.5f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 90.0f),
				glm::vec3(9.9f, 9.0f, 7.5f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 90.0f),
				glm::vec3(9.9f, 9.0f, 6.5f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(1.0f, 0.0f, 2.0f)
				, glm::vec3(-90.0f, 0.0f, 0.0f),
				glm::vec3(7.5f, 1.0f, 9.99f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(1.0f, 0.0f, 2.0f)
				, glm::vec3(-90.0f, 0.0f, 0.0f),
				glm::vec3(6.5f, 1.0f, 9.99f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj"
				, glm::vec3(1.0f, 0.0f, 2.0f),
				glm::vec3(90.0f, 0.0f, 0.0f),
				glm::vec3(7.5f, 7.0f, -9.99f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj"
				, glm::vec3(1.0f, 0.0f, 2.0f),
				glm::vec3(90.0f, 0.0f, 0.0f),
				glm::vec3(6.5f, 7.0f, -9.99f),
				"Texture/realwhite.png"));

		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj"
				, glm::vec3(1.0f, 0.0f, 2.0f),
				glm::vec3(180.0f, 0.0f, 0.0f),
				glm::vec3(5.5f, 6.0f, 1.0f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj"
				, glm::vec3(1.0f, 0.0f, 2.0f),
				glm::vec3(180.0f, 0.0f, 0.0f),
				glm::vec3(6.5f, 6.0f, 1.0f),
				"Texture/realwhite.png"));

		m_pButtons.push_back(
			new Button(2.0f, glm::vec3(7.0f, 6.0f, -9.0f)));

		// transparent wall
		m_pFloor.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(2.0f, 0.1f, 2.0f),
				glm::vec3(0.0f), glm::vec3(7.0f, 5.99f, -9.0f),
				"Texture/alphablue.png"));
		m_pFloor.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(2.0f, 0.1f, 2.0f),
				glm::vec3(0.0f), glm::vec3(-9.0f, 8.0f, 7.0f),
				"Texture/alphablue.png"));
		m_pGlasses.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(3.0f, 0.1f, 2.0f),
				glm::vec3(0.0f, 0.0f, 90.0f),
				glm::vec3(5.05f, 1.5f, 1.0f),
				"Texture/alphared.png"));
		m_pGlasses.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(3.0f, 0.1f, 2.0f),
				glm::vec3(0.0f, 0.0f, 90.0f),
				glm::vec3(6.95f, 1.5f, 1.0f),
				"Texture/alphared.png"));
		m_pGlasses.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(2.0f, 0.1f, 3.0f),
				glm::vec3(90.0f, 0.0f, 0.0f),
				glm::vec3(6.f, 1.5f, 2.05f),
				"Texture/alphared.png"));
		m_pGlasses.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(2.0f, 0.1f, 3.0f),
				glm::vec3(90.0f, 0.0f, 0.0f),
				glm::vec3(6.0f, 1.5f, -0.05f),
				"Texture/alphared.png"));
		m_pGlasses.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(10.0f, 0.1f, 20.0f),
				glm::vec3(0.0f, 0.0f, 90.0f),
				glm::vec3(0.0f, 3.0f, 0.0f),
				"Texture/alphablue.png"));
		break;
	case 2:
		m_pPlayer->setTranslate(glm::vec3(9.5f, 5.0f, -9.5f));
		m_pCubes.push_back(
			new Cube("Objs/PortalCube.obj",
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(0.0f),
				glm::vec3(8.5f, 0.f, 9.0f),
				"Texture/PortalCube.jpg"));
		m_pCubes.push_back(
			new Cube("Objs/PortalCube.obj",
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(0.0f),
				glm::vec3(-8.5f, 0.f, 9.0f),
				"Texture/PortalCube.jpg"));
		// portal walls
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(1.0f, 0.0f, 2.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(9.5f, 0.01f, 9.0f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(1.0f, 0.0f, 2.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(8.5f, 0.01f, 9.0f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(1.0f, 0.0f, 2.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(7.5f, 0.01f, 9.0f),
				"Texture/realwhite.png"));

		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(1.0f, 0.0f, 2.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(-9.5f, 0.01f, 9.0f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(1.0f, 0.0f, 2.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(-8.5f, 0.01f, 9.0f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(1.0f, 0.0f, 2.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(-7.5f, 0.01f, 9.0f),
				"Texture/realwhite.png"));

		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 180.0f),
				glm::vec3(-9.f, 9.f, -9.5f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 180.0f),
				glm::vec3(-9.f, 9.f, -8.5f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 7.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 180.0f),
				glm::vec3(-9.f, 9.f, -7.5f),
				"Texture/realwhite.png"));

		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(1.0f, 0.0f, 2.0f),
				glm::vec3(180.0f, 0.0f, 0.0f),
				glm::vec3(1.f, 7.f, 0.0f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(1.0f, 0.0f, 2.0f),
				glm::vec3(180.0f, 0.0f, 0.0f),
				glm::vec3(0.f, 7.f, 0.0f),
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(1.0f, 0.0f, 2.0f),
				glm::vec3(180.0f, 0.0f, 0.0f),
				glm::vec3(-1.0f, 7.f, 0.0f),
				"Texture/realwhite.png"));

		// button
		m_pButtons.push_back(
			new Button(2.0f, glm::vec3(-8.5f, 0.01f, -8.5f)));
		m_pButtons.push_back(
			new Button(2.0f, glm::vec3(0.f, 0.01f, 0.0f)));

		// transparent wall
		m_pGlasses.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(3.0f, 0.0f, 2.0f),
				glm::vec3(180.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 6.99f, 0.0f),
				"Texture/alphared.png"));

		m_pFloor.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(1.1f, 0.0f, 1.1f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(9.5f, 4.0f, -9.5f),
				"Texture/alphablue.png"));

		m_pFloor.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(1.1f, 0.0f, 1.1f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(9.5f, 5.2f, -9.5f),
				"Texture/alphablue.png"));

		m_pGlasses.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(1.2f, 1.0f, 0.1f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(9.5f, 4.3f, -9.0f),
				"Texture/alphablue.png"));
		m_pGlasses.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(1.2f, 1.0f, 0.1f),
				glm::vec3(0.0f, 90.0f, 0.0f),
				glm::vec3(9.f, 4.3f, -9.5f),
				"Texture/alphablue.png"));
			break;

		default:
			printf("Game Over\n");
			break;
	}


	// cam setting
	m_tCamera = cam;
	m_tCamera.fpsMode = true;

	if (m_tCamera.fpsMode) {
		m_tCamera.vEYE = m_pPlayer->getTranslateVec();
		m_tCamera.vAT = m_pPlayer->getFoward();
	}
	else {
		m_tCamera = cam;
	}
}

Scene::~Scene()
{

	for (int i = 0; i < 2; ++i)
		if (m_pPortal[i]) delete m_pPortal[i];

	for (auto& floor : m_pFloor) delete floor;
	for (auto& wall : m_pWalls) delete wall;
	for (auto& glass : m_pGlasses)delete glass;
	for (auto& glass : m_pPortalWalls)delete glass;
	for (auto& button : m_pButtons)delete button;
	for (auto& cube : m_pCubes) delete cube;

	m_pFloor.clear();	
	m_pWalls.clear();
	m_pGlasses.clear();
	m_pPortalWalls.clear();
	m_pButtons.clear();
	m_pCubes.clear();

	delete m_pPlayer;
}

void Scene::input()
{
	// player move here
	if (GetAsyncKeyState('W') & 0x8000) m_pPlayer->input('w');
	if (GetAsyncKeyState('S') & 0x8000) m_pPlayer->input('s');
	if (GetAsyncKeyState('A') & 0x8000) m_pPlayer->input('a');
	if (GetAsyncKeyState('D') & 0x8000) m_pPlayer->input('d');
	if (GetAsyncKeyState('E') & 0x0001) m_pPlayer->input('e');
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)m_pPlayer->setJump();

	//if (m_bClear && GetAsyncKeyState(VK_RETURN) & 0x0001) CORE->changeScene(m_iSceneNum + 1);

	if (GetAsyncKeyState('M') & 0x0001) {
		glm::vec3 temp = m_pPlayer->getTranslateVec();
		printVector(temp);

		if (m_pPortal[0] && m_pPortal[1]) {
			glm::mat4 portalCam = getPortalView(m_pPortal[0], m_pPortal[1]);
			glm::vec3 eye(portalCam[3][0], portalCam[3][1], portalCam[3][2]);
			printVector(eye);
		}
	}

}

void Scene::update(float frameTime)
{
	glm::vec3 foward;
	//----------------------------------------------
	// update here
	//----------------------------------------------
	if (m_tCamera.fpsMode) {
		foward = m_tCamera.vAT;
		foward.y = 0;
		foward = glm::normalize(foward);
	}
	else {
		foward = m_tCamera.vEYE;
		foward.y = 0;
		foward = -glm::normalize(foward);
	}
	m_pPlayer->setForward(foward);

	//----------------------------------------------
	// update objs
	//----------------------------------------------
	m_pPlayer->update(frameTime);
	for (auto& cube : m_pButtons) 
		cube->update(frameTime);
	for (auto& cube : m_pCubes) {
		if (cube->isFollowing()) cube->setTranslate(m_pPlayer->getTranslateVec());
		else cube->update(frameTime);
	}
	

	//----------------------------------------------
	// collide check
	//----------------------------------------------
	//		player, cube - floor
	glm::vec3 playerMin = m_pPlayer->getTranslateVec() - m_pPlayer->getScaleVec() / 2.0f;
	glm::vec3 playerMax = m_pPlayer->getTranslateVec() + m_pPlayer->getScaleVec() / 2.0f;
	for (auto& floor : m_pFloor) {
		glm::vec3 floorMin = floor->getTranslateVec() - floor->getScaleVec() / 2.0f;
		glm::vec3 floorMax = floor->getTranslateVec() + floor->getScaleVec() / 2.0f;
		if (aabbCollideCheck(playerMin, playerMax, floorMin, floorMax))
			m_pPlayer->moveBack(glm::vec3(0.0f, 1.0f, 0.0f));

		for (auto& cube : m_pCubes) {
			glm::vec3 cubeMin = cube->getTranslateVec() - cube->getScaleVec() / 5.0f;
			glm::vec3 cubeMax = cube->getTranslateVec() + cube->getScaleVec() / 5.0f;
			if (aabbCollideCheck(cubeMin, cubeMax, floorMin, floorMax))
				cube->moveBack(glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}


	//----------------------------------------------
	//		player - portal
	if (m_pPortal[0] && m_pPortal[1]) {
		glm::vec3 origin = m_pPlayer->getFoward();
		glm::vec3 oridir = m_pPlayer->getDir();

		glm::vec3 playerPivot = m_pPlayer->getTranslateVec();
		glm::vec3 playerSize = m_pPlayer->getScaleVec() / 2.0f;
		for (int i = 0; i < 2; ++i) {
			glm::vec3 portalPivot = m_pPortal[i]->getTranslateVec();
			glm::vec3 portalSize = m_pPortal[i]->getScaleVec() / 2.0f;
			if (aabbCollideCheck((playerPivot - playerSize), (playerPivot + playerSize), (portalPivot - portalSize), (portalPivot + portalSize))) {
				// set new Forward
				glm::vec3 distRot = m_pPortal[!i]->getRotateVec();
				glm::vec3 srcRot = m_pPortal[i]->getRotateVec();

				// rot offset
				glm::vec3 rotOffset = distRot - srcRot;
				//rotOffset.y += 180.0f;
				// 
				if (glm::length(rotOffset) <= 0.1f) {
					rotOffset = glm::vec3(0.0f, 180.0f, 0.0f);
				}
				
				else if (abs(rotOffset.y) >= 179.0f && (rotOffset.y) <= 181.0f) {
					rotOffset.y = 0;
				}
				glm::mat4 rotMat(1.0f);
				rotMat = glm::rotate(rotMat, glm::radians(-rotOffset.x), glm::vec3(1.0f, 0.0f, 0.0f));
				rotMat = glm::rotate(rotMat, glm::radians(-rotOffset.y), glm::vec3(0.0f, 1.0f, 0.0f));
				rotMat = glm::rotate(rotMat, glm::radians(-rotOffset.z), glm::vec3(0.0f, 0.0f, 1.0f));

				//rotMat = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * rotMat;

				// rotate camera
				if (m_tCamera.fpsMode) {
					m_tCamera.pitch += rotOffset.z;
					m_tCamera.yaw += rotOffset.y;
					m_tCamera.vAT = rotMat * glm::vec4(m_tCamera.vAT, 0.0f);
				}
				else {
					m_tCamera.pitch += rotOffset.z;
					m_tCamera.yaw += rotOffset.y;
					m_tCamera.vEYE = rotMat * glm::vec4(m_tCamera.vEYE, 0.0f);
				}
				m_tCamera.pitch = int(m_tCamera.pitch + 90.0f) % 360 - 90.0f;
				if (m_tCamera.pitch > 89.0f) m_tCamera.pitch = 89.0f;
				else if (m_tCamera.pitch < -89.0f) m_tCamera.pitch = -89.0f;

				// translate player
				//glm::mat4 tempMat = getPortalView(m_pPortal[i], m_pPortal[!i]);
				//glm::vec3 pos = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
				//	glm::vec4(tempMat[3][0], playerPivot.y, tempMat[3][2], 1.0f);

				//m_pPlayer->setTranslate(pos);


				glm::vec3 offset = m_pPortal[!i]->getTranslateVec() - m_pPortal[i]->getTranslateVec();
				
				m_pPlayer->setTranslate(playerPivot + offset);

				glm::vec3 befDir = m_pPlayer->getDir();
				glm::vec3 tempDir = rotMat * glm::vec4(befDir, 0.0f);
				m_pPlayer->setDir(tempDir);
				m_pPlayer->hit();

#ifdef _DEBUG
				printf("befDir : ");
				printVector(befDir);
				printf("rotOff : ");
				printVector(rotOffset);
				printf("newDir : ");
				printVector(tempDir);
#endif
				// move a little
				if (glm::length(rotOffset) <= 0.1f) m_pPlayer->moveLittle(frameTime * 100);
				m_pPlayer->moveLittle(frameTime * 50);
				break;
			}
		}
	}

	//----------------------------------------------
	//		cube - portal
	if (m_pPortal[0] && m_pPortal[1]) {
		for (auto cube : m_pCubes) {
			if (cube->isFollowing()) continue;
			glm::vec3 cubeMin = cube->getTranslateVec() - cube->getScaleVec() / 2.0f;
			glm::vec3 cubeMax = cube->getTranslateVec() + cube->getScaleVec() / 2.0f;
			for (int i = 0; i < 2; ++i) {
				glm::vec3 portalMin = m_pPortal[i]->getTranslateVec() - m_pPortal[i]->getScaleVec() / 2.0f;
				glm::vec3 portalMax = m_pPortal[i]->getTranslateVec() + m_pPortal[i]->getScaleVec() / 2.0f;

				if (aabbCollideCheck(portalMin, portalMax, cubeMin, cubeMax)) {
					// set new Forward
					glm::vec3 distRot = m_pPortal[!i]->getRotateVec();
					glm::vec3 srcRot = m_pPortal[i]->getRotateVec();

					// rot offset
					glm::vec3 rotOffset = distRot - srcRot;
					//rotOffset.y += 180.0f;
					// 
					if (glm::length(rotOffset) <= 0.1f) {
						rotOffset = glm::vec3(0.0f, 180.0f, 0.0f);
					}
					else if (abs(rotOffset.y) >= 179.0f && (rotOffset.y) <= 181.0f) {
						rotOffset.y = 0;
					}
					else if (abs(rotOffset.z) >= 179.0f && (rotOffset.z) <= 181.0f) {
						rotOffset.z = 0;
					}
					glm::mat4 rotMat(1.0f);
					rotMat = glm::rotate(rotMat, glm::radians(-rotOffset.x), glm::vec3(1.0f, 0.0f, 0.0f));
					rotMat = glm::rotate(rotMat, glm::radians(-rotOffset.y), glm::vec3(0.0f, 1.0f, 0.0f));
					rotMat = glm::rotate(rotMat, glm::radians(-rotOffset.z), glm::vec3(0.0f, 0.0f, 1.0f));

					glm::vec3 offset = m_pPortal[!i]->getTranslateVec() - m_pPortal[i]->getTranslateVec();

					cube->setTranslate(cube->getTranslateVec() + offset);

					printVector(rotOffset);

					if (glm::length(rotOffset) <= 0.1f) cube->moveLittle(frameTime * 100);
					cube->moveLittle(frameTime * 50);
				}
			}
		}
	}

	//----------------------------------------------
	//		player - walls
	if (!m_pPlayer->bIsHit()) {
		glm::vec3 playerMin = m_pPlayer->getTranslateVec() - m_pPlayer->getScaleVec() / 2.0f;
		glm::vec3 playerMax = m_pPlayer->getTranslateVec() + m_pPlayer->getScaleVec() / 2.0f;
		for (const auto& wall : m_pWalls) {
			glm::vec3 wallMin = wall->getTranslateVec() - wall->getScaleVec() / 2.0f;
			glm::vec3 wallMax = wall->getTranslateVec() + wall->getScaleVec() / 2.0f;

			if (aabbCollideCheck(playerMin, playerMax, wallMin, wallMax)) {
				for (int i = 0; i < 3; i += 2) {
					glm::vec3 min = playerMin;
					glm::vec3 max = playerMax;

					// plus Face
					min[i] = max[i];
					if (aabbCollideCheck(min, max, wallMin, wallMax)) {
						min = playerMin;
						max[i] = min[i];
						// minus Face
						if (aabbCollideCheck(min, max, wallMin, wallMax)) {
							glm::vec3 back(i == 2, 0, i == 0);
							m_pPlayer->moveBack(back);
							break;
						}
					}
				}
			}
		}
		for (const auto& wall : m_pGlasses) {
			glm::vec3 wallMin = wall->getTranslateVec() - wall->getScaleVec() / 2.0f;
			glm::vec3 wallMax = wall->getTranslateVec() + wall->getScaleVec() / 2.0f;

			if (aabbCollideCheck(playerMin, playerMax, wallMin, wallMax)) {
				for (int i = 0; i < 3; i += 2) {
					glm::vec3 min = playerMin;
					glm::vec3 max = playerMax;

					// plus Face
					min[i] = max[i];
					if (aabbCollideCheck(min, max, wallMin, wallMax)) {
						min = playerMin;
						max[i] = min[i];
						// minus Face
						if (aabbCollideCheck(min, max, wallMin, wallMax)) {
							glm::vec3 back(i == 2, 0, i == 0);
							m_pPlayer->moveBack(back);
							break;
						}
					}
				}
			}

		}
	}

	//----------------------------------------------
	//		 player cube
	playerMin = m_pPlayer->getTranslateVec() - m_pPlayer->getScaleVec() / 2.0f;
	playerMax = m_pPlayer->getTranslateVec() + m_pPlayer->getScaleVec() / 2.0f;
	if (m_pPlayer->isHoldOn()) {
		for (auto& cube : m_pCubes) {
			glm::vec3 cubeMin = cube->getTranslateVec() - cube->getScaleVec() / 2.0f;
			glm::vec3 cubeMax = cube->getTranslateVec() + cube->getScaleVec() / 2.0f;
			if (cube->isFollowing()) {
				cube->setFollow(false);
				break;
			}
			else if (aabbCollideCheck(playerMin, playerMax, cubeMin, cubeMax)) {
				cube->setFollow(true);
				break;
			}
		}
	}
	m_pPlayer->offHold();
	
	//----------------------------------------------
	//		cube - buttons		
	bool allClaer = true;
	for (auto& button : m_pButtons) {
		bool bPushed = false;
		//glm::vec3 buttonMin = button->getTranslateVec() - button->getScaleVec() / 2.0f;
		//glm::vec3 buttonMax = button->getTranslateVec() + button->getScaleVec() / 2.0f;
		glm::vec3 buttonMin = button->getButtonTranslateVec() - button->getButtonScaleVec() / 2.0f;
		glm::vec3 buttonMax = button->getButtonTranslateVec() + button->getButtonScaleVec() / 2.0f;
		for (auto& cube : m_pCubes) {
			glm::vec3 cubeMin = cube->getTranslateVec() - cube->getScaleVec() / 2.0f;
			glm::vec3 cubeMax = cube->getTranslateVec() + cube->getScaleVec() / 2.0f;
			if (aabbCollideCheck(buttonMin, buttonMax, cubeMin, cubeMax)) {
				button->setPressState(true);
				bPushed = true;
				break;
			}
		}
		if (!bPushed) {
			allClaer = false;
			button->setPressState(false);
		}
	}
	if (!m_bClear && allClaer) {
		//printf("clear!\nPress Enter!\n");
		m_bClear = true;
	}


	m_fChangeTime += m_bClear * frameTime;
	if (m_fChangeTime >= 5.0f) CORE->changeScene(m_iSceneNum + 1);

	//----------------------------------------------
	// make portal
	//----------------------------------------------
	// do sth like intersect check
	if (m_iShoot) {
		float minLen = INFINITE;
		int cnt = 0;
		glm::vec3 ray = m_tCamera.vAT;
		glm::vec3 pos = m_tCamera.vEYE;
		glm::vec3 normals[6] = {
			{1.0f, 0.0f, 0.0f},
			{-1.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, -1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, -1.0f},
		};
		for (auto const& wall : m_pGlasses) {
			float dist = 0.0f;
			glm::vec3 wallPos = wall->getTranslateVec();
			glm::vec3 wallMin = wallPos - wall->getScaleVec() / 2.0f;
			glm::vec3 wallMax = wallPos + wall->getScaleVec() / 2.0f;

			if(rayAABB(wallMin, wallMax, pos, ray)) minLen = 0.0f;
		}

		printf("minLen : %.2f\tcnt : %d\n", minLen, cnt);

		for (auto const& wall : m_pPortalWalls) {
			glm::vec3 wallPos = wall->getTranslateVec();
			glm::vec3 wallMin = wallPos - wall->getScaleVec() / 2.0f;
			glm::vec3 wallMax = wallPos + wall->getScaleVec() / 2.0f;

			if (rayAABB(wallMin, wallMax, pos, ray)) {
				glm::vec3 normal = wall->getNormal();
				if (glm::length(wall->getTranslateVec() - m_pPlayer->getTranslateVec()) > minLen) continue;

				// make new portal
				if (m_pPortal[m_iShoot - 1]) delete m_pPortal[m_iShoot - 1];

				// set new position
				float lenth = glm::length(wall->getTranslateVec() - m_pPlayer->getTranslateVec());
				lenth -= lenth / 1000.0f;
				glm::vec3 newPos = m_tCamera.vEYE + lenth * ray;

				int faceNum = -1;
				if (normal.x >= 0.9f) faceNum = 1;
				else if (normal.x <= -0.9f) faceNum = 3;
				else if (normal.z >= 0.9f) faceNum = 0;
				else if (normal.z <= -0.9f) faceNum = 2;
				else if (normal.y >= 0.9f) faceNum = 4;
				else faceNum = 5;

#ifdef _DEBUG
				printf("Face Num : %d \t", faceNum);
				printf("normal : ");
				printVector(normal);
#endif // DEBUG
				m_pPortal[m_iShoot - 1] = new Portal(1.0f, faceNum, wall->getTranslateVec(), m_iShoot - 1);

				break;
			}			
		}
		m_iShoot = 0;
	}

	//----------------------------------------------
	// camera update by player
	//----------------------------------------------
	if (m_tCamera.fpsMode) {
		glm::vec3 yPlus = m_pPlayer->getScaleVec();
		yPlus.x = 0;
		yPlus.z = 0;
		m_tCamera.vEYE = m_pPlayer->getTranslateVec() + yPlus;
	}
	else m_tCamera.vAT = m_pPlayer->getTranslateVec();

	//----------------------------------------------
	CORE->updateViewMat();
	m_pPlayer->setDirZero();
}

void Scene::draw(unsigned int shaderNum, int textureBind, bool main)
{
	// draw all
	// floor
	for (auto floor : m_pFloor) 
		floor->draw(shaderNum, textureBind);
	
	// wall
	for (auto wall : m_pWalls) 
		wall->draw(shaderNum, textureBind);
	
	// portal wall
	for (auto portalwall : m_pPortalWalls) 
		portalwall->draw(shaderNum, textureBind);
	
	// empty portal
	if (m_pPortal[0] && !m_pPortal[1]) 
		m_pPortal[0]->draw(shaderNum, textureBind);
	if (!m_pPortal[0] && m_pPortal[1]) 
		m_pPortal[1]->draw(shaderNum, textureBind);

	// cube
	for (auto cube : m_pCubes) {
		if (main && cube->isFollowing()) continue;
		cube->draw(shaderNum, textureBind);
	}

	for (auto button : m_pButtons) {
		button->draw(shaderNum, textureBind);

	}
	
	if (m_tCamera.fpsMode && !main) m_pPlayer->draw(shaderNum, textureBind);

	// glass
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (auto glass : m_pGlasses) 
		glass->draw(shaderNum, textureBind);
	
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH);
}

void Scene::drawPortal(unsigned int shaderNum, int textureBind)
{
	for (int i = 0; i < 2; ++i) {
		if (!m_pPortal[i]) {
			if (m_pPortal[i]) m_pPortal[i]->draw(shaderNum, textureBind);
			return;
		}
	}

	glClearStencil(0);
	glEnable(GL_STENCIL_TEST);
	glClear(GL_STENCIL_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < 2; ++i) {
		// draw portal at stensil buffer
		glClearStencil(0);
		glStencilFunc(GL_NEVER, 0, 0);				// every fragment cant pass test
		glStencilOp(GL_INCR, GL_INCR, GL_INCR);		// always fail, 

		// draw in stensil buffer
		CORE->updateViewMat();
		CORE->m_pMainShader->use();

		m_pPortal[i]->draw(shaderNum, textureBind);

		// move camera to back of the portal
		glm::mat4 viewMat = getPortalView(m_pPortal[i], m_pPortal[!i]);
		//glm::mat4 projMat = m_pPortal[i]->clipProjMat(viewMat, CORE->m_mProjMat);

		CORE->m_pMainShader->setMat4("viewTransform", viewMat);

		// cube map move
		for (int i = 0; i < 4; ++i) viewMat[3][i] = 0.0f;

		CORE->m_pCubeShader->setMat4("viewTransform", viewMat);
		CORE->m_pMainShader->setVec3("viewPos", m_pPortal[i]->getTranslateVec());
		//CORE->m_pMainShader->setMat4("projectionTransform", projMat);

		// change stensil testing mode
		// draw objs on restricted area
		glStencilFunc(GL_LEQUAL, 1, 0xff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

		draw(shaderNum, textureBind);
		CORE->drawSkyCube();

	}
	glDisable(GL_STENCIL_TEST);

	// cant overrite
	GLboolean colorMasks[4];
	GLboolean depthMask;
	glGetBooleanv(GL_COLOR_WRITEMASK, colorMasks);
	glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMask);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_TRUE);

	CORE->updateViewMat();
	CORE->updateProjMat();
	//glDepthFunc(GL_ALWAYS);

	for (int i = 0; i < 2; ++i)
		m_pPortal[i]->draw(shaderNum, textureBind);

	//glDepthFunc(GL_LESS);
	glColorMask(colorMasks[0], colorMasks[1], colorMasks[2], colorMasks[3]);
	glDepthMask(depthMask);


}

void Scene::mouseActFucn(int key, int state, POINT pt)
{
	m_tBefPoint = pt;

	if (CORE->m_bHideCursor) {
		// shoot blue
		if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN) m_iShoot = 1;

		// shoot orange
		if (key == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) m_iShoot = 2;
	}
}

void Scene::moveMouse(POINT pt, bool hideMode)
{
	//if (!m_bDragging && !hideMode) return;

	// rotate camera
	m_tCamera.updatePos(m_tBefPoint.x - pt.x, m_tBefPoint.y - pt.y);
	m_tBefPoint = pt;

	// rotate robot foward
}

void Scene::scrollMouse(int dir)
{
	if (dir > 0) m_tCamera.scroll -= m_tCamera.scroll / 10;
	else m_tCamera.scroll += m_tCamera.scroll / 10;
}

glm::mat4 Scene::getPortalView(Portal* from, Portal* dest)
{
	glm::mat4 temp = m_tCamera.getViewMat() * from->getModelTransform();
	glm::mat4 portalCam =
		temp *
		glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::inverse(dest->getModelTransform());

	return portalCam;
}