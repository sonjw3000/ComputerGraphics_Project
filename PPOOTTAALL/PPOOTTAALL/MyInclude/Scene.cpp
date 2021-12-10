#include "Core.h"
#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "RotatingCube.h"
#include "Portal.h"

Scene::Scene(int sceneNum, CameraVectors& cam) :
	m_pPortal{nullptr, nullptr},
	m_pPlane(nullptr),
	m_iSceneNum(sceneNum)
{
	m_tCamera = cam;

	m_pPlane = new Plane("Objs/Cube.obj", glm::vec3(50.0f, 0.1f, 50.0f), glm::vec3(0.0f), glm::vec3(0.0f), "Texture/bg.png");
	m_pPlayer = new Player(1.0f, glm::vec3(0.0f));

	m_pPortal[0] = new Portal(5.0f, 0, glm::vec3(10.0f, 0.0f, 0.0f));
	m_pPortal[1] = new Portal(5.0f, 2, glm::vec3(0.0f, 0.0f, 10.0f));

	switch (sceneNum) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	}
}

Scene::~Scene()
{
	//delete m_pMeshes;
}

void Scene::input()
{
	// player move here
	if (GetAsyncKeyState('W') & 0x8000) Player::input('w');
	if (GetAsyncKeyState('S') & 0x8000) Player::input('s');
	if (GetAsyncKeyState('A') & 0x8000) Player::input('a');
	if (GetAsyncKeyState('D') & 0x8000) Player::input('d');
}

void Scene::update(float frameTime)
{
	// update here
	glm::vec3 foward = m_tCamera.vEYE;
	foward.y = 0;
	foward = glm::normalize(foward);
	Player::setForward(-foward);
	 
	//----------------------------------------------
	// player move
	m_pPlayer->update(frameTime);

	//----------------------------------------------
	// cubes rotate

	//----------------------------------------------
	// collide check
	// player - floor


	// player - rotating cube


	// player button?

	// player sleeping palyer

	// camera update by player[0]
	m_tCamera.vAT = m_pPlayer->getTranslateVec();
	CORE->updateViewMat();

	// set Player Dir to zero
	Player::setDirZero();
}

void Scene::draw(unsigned int shaderNum, int textureBind)
{
	// draw all
	m_pPlane->draw(shaderNum, textureBind);

	m_pPlayer->draw(shaderNum, textureBind);

	m_pPortal[0]->draw(shaderNum, textureBind);
	m_pPortal[1]->draw(shaderNum, textureBind);

}

void Scene::activeDragging(bool active, POINT pt)
{
	m_bDragging = active;
	m_tBefPoint = pt;
}

void Scene::moveMouse(POINT pt)
{
	if (!m_bDragging) return;

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
