#include "Core.h"
#include "ShaderProgram.h"
#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "RotatingCube.h"
#include "Portal.h"
#include "CollisionCheck.h"


Scene::Scene(int sceneNum, CameraVectors& cam) :
	m_pPortal{nullptr, nullptr},
	m_pPlane(nullptr),
	m_iSceneNum(sceneNum)
{
	m_pPlane = new Plane("Objs/Cube.obj", glm::vec3(20.0f, 0.1f, 20.0f), glm::vec3(0.0f), glm::vec3(0.0f), "Texture/bg.png");
	m_pPlayer = new Player(0.4f, glm::vec3(0.0f));

	//m_pWall[0] = new Plane("Objs/Cube.obj", glm::vec3(10.0f, 0.1f, 20.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(-10.0f,5.0f,0.0f), "Texture/bg.png");	// 로봇이 바라보는 방향 기준 오른쪽 벽
	//m_pWall[1] = new Plane("Objs/Cube.obj", glm::vec3(10.0f, 0.1f, 20.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(10.0f,5.0f,0.0f), "Texture/bg.png");	// 로봇이 바라보는 방향 기준 왼쪽 벽
	//m_pWall[2] = new Plane("Objs/Cube.obj", glm::vec3(20.0f, 0.1f, 10.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.0f,5.0f, -10.0f), "Texture/bg.png");	// 
	//m_pWall[3] = new Plane("Objs/Cube.obj", glm::vec3(20.0f, 0.1f, 10.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.0f, 5.0f, 10.0f), "Texture/bg.png");

	m_pPortal[0] = new Portal(0.4f, 0, glm::vec3(5.0f, 0.0f, 0.0f));
	m_pPortal[1] = new Portal(0.4f, 2, glm::vec3(0.0f, 0.0f, 5.0f));

	switch (sceneNum) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	}

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
	delete m_pPlane;
	delete m_pPlayer;

	for(int i = 0; i < 2; ++i)
		if (m_pPortal[i]) delete m_pPortal[i];

	for (int i = 0; i < 4; ++i)
		if (m_pWall[i]) delete m_pWall[i];
}

void Scene::input()
{
	// player move here
	if (GetAsyncKeyState('W') & 0x8000) m_pPlayer->input('w');
	if (GetAsyncKeyState('S') & 0x8000) m_pPlayer->input('s');
	if (GetAsyncKeyState('A') & 0x8000) m_pPlayer->input('a');
	if (GetAsyncKeyState('D') & 0x8000) m_pPlayer->input('d');
}

void Scene::update(float frameTime)
{
	glm::vec3 foward;
	// update here
	if (m_tCamera.fpsMode) {
		m_tCamera.vEYE = m_pPlayer->getTranslateVec();
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
	// player move
	m_pPlayer->update(frameTime);

	//----------------------------------------------

	//----------------------------------------------
	// collide check
	// player - floor


	// player - portal
	if (m_pPortal[0] && m_pPortal[1]) {
		glm::vec3 playerPivot = m_pPlayer->getTranslateVec();
		for (int i = 0; i < 2; ++i) {
			glm::vec3 portalPivot = m_pPortal[i]->getTranslateVec();
			glm::vec3 portalSize = m_pPortal[i]->getScaleVec();
			if (aabbCollideCheck(playerPivot, playerPivot, portalPivot - portalSize, portalPivot + portalSize)) {
				glm::vec3 distRot = m_pPortal[!i]->getRotateVec();
				glm::vec3 srcRot = m_pPortal[i]->getRotateVec();

				//glm::vec3 rot = distRot - srcRot;
				//printf("%.2f %.2f %.2f \t", temp.x, temp.y, temp.z);

				//glm::vec3 newFow = 

				//m_pPlayer->setForward();
				
			}
		}
	}


	// player button?

	// player sleeping palyer

	// camera update by player
	if (m_tCamera.fpsMode) {
		m_tCamera.vEYE = m_pPlayer->getTranslateVec();
		//m_tCamera.vAT = m_pPlayer->getFoward();
	}
	else {
		m_tCamera.vAT = m_pPlayer->getTranslateVec();
	}
	CORE->updateViewMat();

	printf("EYE : %.2f %.2f %.2f \AT : %.2f %.2f %.2f\n", 
		m_tCamera.vEYE.x + m_tCamera.vAT.x, m_tCamera.vEYE.y + m_tCamera.vAT.y, m_tCamera.vEYE.z + m_tCamera.vAT.z,
		m_tCamera.vAT.x, m_tCamera.vAT.y, m_tCamera.vAT.z);

	// set Player Dir to zero
	m_pPlayer->setDirZero();
}

void Scene::draw(unsigned int shaderNum, int textureBind)
{
	// draw all
	m_pPlane->draw(shaderNum, textureBind);

	//m_pWall[0]->draw(shaderNum, textureBind);
	//m_pWall[1]->draw(shaderNum, textureBind);
	//m_pWall[2]->draw(shaderNum, textureBind);
	//m_pWall[3]->draw(shaderNum, textureBind);

	m_pPlayer->draw(shaderNum, textureBind);
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
		CORE->m_pCubeShader->setMat4("viewTransform", viewMat);
		CORE->m_pMainShader->setMat4("viewTransform", viewMat);
		CORE->m_pMainShader->setVec3("viewPos", m_pPortal[i]->getTranslateVec());

		// change stensil testing mode
		// draw objs on restricted area
		glStencilFunc(GL_LEQUAL, 1, 0xff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

		draw(shaderNum, textureBind);

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
	for (int i = 0; i < 2; ++i)
		m_pPortal[i]->draw(shaderNum, textureBind);

	glColorMask(colorMasks[0], colorMasks[1], colorMasks[2], colorMasks[3]);
	glDepthMask(depthMask);

	
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

glm::mat4 Scene::getPortalView(Portal* from, Portal* dist)
{
	glm::mat4 temp = m_tCamera.getViewMat() * from->getModelTransform();
	glm::mat4 portalCam =
		temp *
		glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::inverse(dist->getModelTransform());

	return portalCam;
}
