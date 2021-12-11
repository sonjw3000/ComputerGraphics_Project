#include "Core.h"
#include "ShaderProgram.h"
#include "Scene.h"
#include "Plane.h"
#include "Cube.h"
#include "Player.h"
#include "Portal.h"
#include "CollisionCheck.h"


inline void printVector(glm::vec3 vec)
{
	printf("%.2f, %.2f, %.2f\n", vec.x, vec.y, vec.z);
}


Scene::Scene(int sceneNum, CameraVectors& cam) :
	m_pPortal{nullptr, nullptr},
	m_pFloor(nullptr),
	m_iSceneNum(sceneNum)
{
	m_pFloor = new Plane("Objs/Plane.obj", glm::vec3(21.0f, 0.1f, 21.0f), glm::vec3(0.0f), glm::vec3(0.0f), "Texture/bg.png");
	m_pPlayer = new Player(0.4f, glm::vec3(0.0f));

	// right
	m_pWalls.push_back(
		new Plane("Objs/Plane.obj",
			glm::vec3(10.0f, 0.0f, 20.0f), 
			glm::vec3(0.0f, 0.0f, -90.0f), 
			glm::vec3(-10.0f, 5.0f, 0.0f), 
			"Texture/wall.png"));

	// left
	m_pWalls.push_back(
		new Plane("Objs/Plane.obj",
			glm::vec3(10.0f, 0.0f, 20.0f),
			glm::vec3(0.0f, 0.0f, 90.0f),
			glm::vec3(10.0f, 5.0f, 0.0f), 
			"Texture/wall.png"));

	// back
	m_pWalls.push_back(
		new Plane("Objs/Plane.obj", 
			glm::vec3(20.0f, 0.0f, 10.0f),
			glm::vec3(90.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 5.0f, -10.0f),
			"Texture/wall.png"));

	// front
	m_pWalls.push_back(
		new Plane("Objs/Plane.obj",
			glm::vec3(20.0f, 0.0f, 10.0f), 
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

		// portal walls
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj", 
				glm::vec3(2.0f, 0.0f, 2.0f), 
				glm::vec3(90.0f, 0.0f, 0.0f), 
				glm::vec3(5.0f, 1.0f, 9.99f), 
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 2.0f), 
				glm::vec3(0.0f, 0.0f, 90.0f), 
				glm::vec3(-9.99f, 1.0f, 1.0f), 
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 2.0f), 
				glm::vec3(0.0f, 0.0f, 90.0f), 
				glm::vec3(-9.99f, 6.0f, 7.0f), 
				"Texture/realwhite.png"));

		// wall
		m_pWalls.push_back(
			new Plane("Objs/roundPlane.obj",
				glm::vec3(2.0f, 0.0f, 2.0f),
				glm::vec3(0.0f)
				, glm::vec3(9.0f, 0.01f, -9.0f),
				"Texture/realred.png"));

		// transparent wall
		m_pGlasses.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(2.0f, 0.1f, 2.0f),
				glm::vec3(0.0f),
				glm::vec3(-9.0f, 4.99f, 7.0f),
				"Texture/alphablue.png"));
		m_pGlasses.push_back(
			new Plane("Objs/Cube.obj",
				glm::vec3(1.0f, 0.1f, 20.0f),
				glm::vec3(0.0f, 0.0f, 90.0f),
				glm::vec3(0.0f, 0.5f, 0.0f),
				"Texture/alphablue.png"));		// �߾� �и���
		m_pGlasses.push_back(
			new Plane("Objs/Cube.obj"
				, glm::vec3(4.0f, 0.1f, 20.0f),
				glm::vec3(0.0f, 0.0f, 90.0f),
				glm::vec3(0.0f, 3.8f, 0.0f),
				"Texture/alphablue.png"));		// �߾� �и���

		m_pPortal[0] = new Portal(1.0f, 2, glm::vec3(5.0f, 0.0f, 10.0f));
		m_pPortal[1] = new Portal(1.0f, 1, glm::vec3(-10.0f, 0.0f, 1.0f));
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
				glm::vec3(2.0f, 0.0f, 2.0f),
				glm::vec3(0.0f, 0.0f, 90.0f),
				glm::vec3(-9.99f, 1.0f, 1.0f), 
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 2.0f),
				glm::vec3(0.0f, 0.0f, 90.0f), 
				glm::vec3(-9.99f, 9.0f, 7.0f), 
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 2.0f),
				glm::vec3(0.0f, 0.0f, 90.0f), 
				glm::vec3(9.99f, 9.0f, 7.0f), 
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 2.0f)
				, glm::vec3(90.0f, 0.0f, 0.0f),
				glm::vec3(7.f, 1.0f, 9.99f), 
				"Texture/realwhite.png"));
		m_pPortalWalls.push_back(
			new Plane("Objs/Plane.obj"
				, glm::vec3(2.0f, 0.0f, 2.0f),
				glm::vec3(90.0f, 0.0f, 0.0f),
				glm::vec3(7.f, 7.0f, -9.99f), 
				"Texture/realwhite.png"));

		// button
		m_pWalls.push_back(
			new Plane("Objs/roundPlane.obj",
				glm::vec3(2.0f, 0.0f, 2.0f),
				glm::vec3(0.0f), glm::vec3(7.0f, 6.0f, -9.0f),
				"Texture/realred.png"));

		// transparent wall
		m_pGlasses.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 2.0f), 
				glm::vec3(0.0f), glm::vec3(7.0f, 5.99f, -9.0f),
				"Texture/alphablue.png"));
		m_pGlasses.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(2.0f, 0.0f, 2.0f), 
				glm::vec3(0.0f), glm::vec3(-9.0f, 8.0f, 7.0f), 
				"Texture/alphablue.png"));
		m_pGlasses.push_back(
			new Plane("Objs/Plane.obj",
				glm::vec3(10.0f, 0.0f, 20.0f),
				glm::vec3(0.0f, 0.0f, 90.0f), 
				glm::vec3(0.0f, 3.0f, 0.0f), 
				"Texture/alphablue.png"));
		break;
	case 2:
		//asdfasdfasfas
		//asdfasdfa
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
	delete m_pFloor;
	delete m_pPlayer;

	for(int i = 0; i < 2; ++i)
		if (m_pPortal[i]) delete m_pPortal[i];

	for (auto& wall : m_pWalls) {
		delete wall;
	}
	m_pWalls.clear();
	for (auto& cube : m_pCubes) {
		delete cube;
	}
	m_pCubes.clear();
}

void Scene::input()
{
	// player move here
	if (GetAsyncKeyState('W') & 0x8000) m_pPlayer->input('w');
	if (GetAsyncKeyState('S') & 0x8000) m_pPlayer->input('s');
	if (GetAsyncKeyState('A') & 0x8000) m_pPlayer->input('a');
	if (GetAsyncKeyState('D') & 0x8000) m_pPlayer->input('d');
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)m_pPlayer->setJump();

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
		glm::vec3 yPlus = m_pPlayer->getScaleVec() / 2.0f;
		yPlus.x = 0;
		yPlus.z = 0;
		m_tCamera.vEYE = m_pPlayer->getTranslateVec() + yPlus;
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

	//----------------------------------------------
	// collide check
	//----------------------------------------------
	// player - floor
	glm::vec3 playerMin = m_pPlayer->getTranslateVec() - m_pPlayer->getScaleVec() / 2.0f;
	glm::vec3 playerMax = m_pPlayer->getTranslateVec() + m_pPlayer->getScaleVec() / 2.0f;
	glm::vec3 floorMin = m_pFloor->getTranslateVec() - m_pFloor->getScaleVec() / 2.0f;
	glm::vec3 floorMax = m_pFloor->getTranslateVec() + m_pFloor->getScaleVec() / 2.0f;
	if (aabbCollideCheck(playerMin, playerMax, floorMin, floorMax)) 
		m_pPlayer->moveBack(glm::vec3(0.0f, playerMin.y - floorMax.y, 0.0f));

	//----------------------------------------------
	// player - portal
	if (m_pPortal[0] && m_pPortal[1]) {
		bool bDoubleHit = false;

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

				glm::mat4 rotMat(1.0f);
				rotMat = glm::rotate(rotMat, glm::radians(-rotOffset.x), glm::vec3(1.0f, 0.0f, 0.0f));
				rotMat = glm::rotate(rotMat, glm::radians(-rotOffset.y), glm::vec3(0.0f, 1.0f, 0.0f));
				rotMat = glm::rotate(rotMat, glm::radians(-rotOffset.z), glm::vec3(0.0f, 0.0f, 1.0f));

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
				glm::vec3 offset = m_pPortal[!i]->getTranslateVec() - m_pPortal[i]->getTranslateVec();
				m_pPlayer->setTranslate(playerPivot + offset);
				printf("%.2f %.2f %.2f\n", offset.x, offset.y, offset.z);

				// move a little
				m_pPlayer->moveLittle(frameTime);
				break;
			}
		}
	}

	//----------------------------------------------
	// player - walls
	for (const auto& wall : m_pWalls) {
		glm::vec3 wallMin = wall->getTranslateVec() - wall->getScaleVec() / 2.0f;
		glm::vec3 wallMax = wall->getTranslateVec() + wall->getScaleVec() / 2.0f;
		
		if (aabbCollideCheck(playerMin, playerMax, wallMin, wallMax)) {
			//printf("holly shit ");
			glm::vec3 normal = wall->getNormal();
			glm::vec3 offset = wall->getTranslateVec() - m_pPlayer->getTranslateVec();
			glm::vec3 size = glm::abs(m_pPlayer->getScaleVec() / 2.0f) * normal;
			glm::vec3 move = size - normal * offset;
			printVector(normal);
			//m_pPlayer->moveBack(-move);
		}
	}

	//----------------------------------------------
	// player button?

	//----------------------------------------------
	// camera update by player
	//----------------------------------------------
	if (m_tCamera.fpsMode) m_tCamera.vEYE = m_pPlayer->getTranslateVec();
	else m_tCamera.vAT = m_pPlayer->getTranslateVec();
	
	//----------------------------------------------
	CORE->updateViewMat();
	m_pPlayer->setDirZero();
}

void Scene::draw(unsigned int shaderNum, int textureBind, bool main)
{
	// draw all
	m_pFloor->draw(shaderNum, textureBind);

	for (auto wall : m_pWalls) {
		wall->draw(shaderNum, textureBind);
	}

	//for (auto portalwall : m_pPortalWalls) {
	//	portalwall->draw(shaderNum, textureBind);
	//}
	//m_pPortal[0]->draw(shaderNum, textureBind);
	//m_pPortal[1]->draw(shaderNum, textureBind);
	for (auto cube : m_pCubes) {
		cube->draw(shaderNum, textureBind);
	}
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (auto glass : m_pGlasses) {
		glass->draw(shaderNum, textureBind);
	}
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH);
	if(m_tCamera.fpsMode && !main) m_pPlayer->draw(shaderNum, textureBind);
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
	glDepthFunc(GL_ALWAYS);

	for (int i = 0; i < 2; ++i) 
		m_pPortal[i]->draw(shaderNum, textureBind);
	
	glDepthFunc(GL_LESS);
	glColorMask(colorMasks[0], colorMasks[1], colorMasks[2], colorMasks[3]);
	glDepthMask(depthMask);

	
}

void Scene::activeDragging(bool active, POINT pt)
{
	m_bDragging = active;
	m_tBefPoint = pt;
}

void Scene::moveMouse(POINT pt, bool hideMode)
{
	if (!m_bDragging && !hideMode) return;

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
