#include "Core.h"
#include "Mesh.h"
#include "Timer.h"
#include "Scene.h"
#include "ShaderProgram.h"
#include "CubeMap.h"
#include "DepthMap.h"

Single* Single::m_pInst = nullptr;


Single::Single()
{
	m_pScene = nullptr;
}

Single::~Single()
{
	delete m_pScene;
	delete m_pMainShader;
	delete m_pCube;
	delete m_pSkyCube;
}

bool Single::init(int argc, char* argv[], int sizex, int sizey)
{
	CORE->m_tWndSize = { sizex, sizey };


	// Initialize Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(sizex, sizey);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("PPOORRTTAALL");


	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unable to initialize GLEW!!" << std::endl;
		return false;
		//exit(EXIT_FAILURE);
	}
	else std::cout << "GLEW initialized \n" << std::endl;

	// init
	initializeProgram();

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_CULL_FACE);

	// Callback Functions
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardChecker);
	glutMotionFunc(mouseMove);
	glutMouseFunc(mouseAct);
	glutMouseWheelFunc(mouseWheel);
	glutPassiveMotionFunc(mouseMoving);

	glutIdleFunc(gameLoop);

	// init completed
	return true;
}

void Single::run()
{
	CORE->m_pTimer = new Timer;
	//m_pTimer->resetTimer();

	glutMainLoop();
}

void Single::changeScene(int sceneNum)
{
	if (!m_pScene) delete m_pScene;
	CameraVectors temp;
	temp.pitch = 0.0f;
	temp.yaw = 90.0f;
	temp.vEYE = glm::vec3(1.0f);
	temp.vAT = glm::vec3(0.0f);
	temp.vUP = glm::vec3(0.0f, 1.0f, 0.0f);
	temp.scroll = 5.0f;

	m_pScene = new Scene(sceneNum, temp);

	if (sceneNum) updateViewMat();
}

void Single::endProgram()
{
	glutLeaveMainLoop();
}

void Single::initializeProgram()
{
	// init scene
	changeScene(0);

	// init shaders
	m_pMainShader = new ShaderProgram("Shader/vertex_1.glsl", "Shader/fragment_1.glsl");
	m_pShadowShader = new ShaderProgram("Shader/1pass_vertex.glsl","Shader/1pass_fragment.glsl");
	m_pCubeShader = new ShaderProgram("Shader/vertex_cube.glsl", "Shader/fragment_cube.glsl");
	// init mainshader transform
	//-------------------------------------------------------------------------------------
	// main shader
	m_pMainShader->use();

	// proj mat
	m_mProjMat =
		glm::perspective(glm::radians(45.0f), float(m_tWndSize.cx) / float(m_tWndSize.cy), 0.01f, 300.0f);
	m_pMainShader->setMat4("projectionTransform", m_mProjMat);

	// view mat
	glm::mat4 viewTransform = m_pScene->m_tCamera.getViewMat();
	m_pMainShader->setMat4("viewTransform", viewTransform);

	// light pos;
	glm::vec3 viewPos = m_pScene->m_tCamera.getSight();
	m_vLightPos = glm::vec3(0.f, 25.0f, 0.f);
	m_vLightColor = glm::vec3(1.0f);

	m_pMainShader->setVec3("viewPos", viewPos);
	m_pMainShader->setVec3("lightPos", m_vLightPos);
	m_pMainShader->setVec3("lightColor", m_vLightColor);
	//-------------------------------------------------------------------------------------
	// cube shader
	m_pCube = new Mesh("Objs/Cube.obj", glm::vec3(1.0f), glm::vec3(0.0f), glm::vec3(0.0f));
	m_pSkyCube = new CubeMap("Texture/cube/c");

	m_pCubeShader->use();
	m_pCubeShader->setMat4("projectionTransform", m_mProjMat);
	m_pCubeShader->setMat4("viewTransform", glm::mat3(viewTransform));
	//-------------------------------------------------------------------------------------
	// shadow shader
	m_pShadowShader->use();
	glm::mat4 shdwProj = glm::ortho(-30.0f, 30.0f, -30.0f, 30.0f, -10.0f, 300.0f);
	glm::mat4 lightView = glm::lookAt(m_vLightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_pShadowShader->setMat4("lightSpace", (shdwProj * lightView));
	//-------------------------------------------------------------------------------------
	m_pMainShader->use();
	m_pMainShader->setMat4("lightVP", (shdwProj * lightView));

	m_pDepthMap = new DepthMap(8184, 8184);

	m_pMainShader->setInt("shadowMap", 0);
	m_pMainShader->setInt("texture0", 1);
}

void Single::updateViewMat()
{
	glm::mat4 viewTransform = m_pScene->m_tCamera.getViewMat();

	// view mat
	// main
	m_pMainShader->use();
	m_pMainShader->setMat4("viewTransform", viewTransform);
	m_pMainShader->setVec3("viewPos", m_pScene->m_tCamera.getSight());

	// cube
	m_pCubeShader->use();
	m_pCubeShader->setMat4("viewTransform", glm::mat3(viewTransform));
}

void Single::updateProjMat()
{
	m_pMainShader->use();

	// proj mat
	//m_mProjMat =
	//	glm::perspective(glm::radians(45.0f), float(m_tWndSize.cx) / float(m_tWndSize.cy), 0.1f, 300.0f);
	m_pMainShader->setMat4("projectionTransform", m_mProjMat);
}

void Single::drawSkyCube()
{
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_FRONT);
	m_pCubeShader->use();

	// bind tex
	m_pSkyCube->bindTexture(0);
	// draw cube
	m_pCube->draw();
	glCullFace(GL_BACK);
	glDepthFunc(GL_LESS);
}

void Single::drawScene()
{
	//--------------------------------------------------------------
	// 1st pass
	glCullFace(GL_FRONT);
	CORE->m_pShadowShader->use();

	CORE->m_pDepthMap->useTexMap();
	CORE->m_pScene->draw(CORE->m_pShadowShader->getProgram(), 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//--------------------------------------------------------------
	// 2nd pass
	glCullFace(GL_BACK);
	glViewport(0, 0, CORE->m_tWndSize.cx, CORE->m_tWndSize.cy);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	// draw all
	// first should draw portal
	// stensil buffer
	CORE->m_pMainShader->use();
	CORE->m_pDepthMap->bindTexture(0);

	// draw stencil pattern

	// portal draw
	CORE->m_pScene->drawPortal(CORE->m_pMainShader->getProgram(), 1);

	// draw all
	CORE->m_pMainShader->use();
	CORE->m_pDepthMap->bindTexture(0);
	CORE->m_pScene->draw(CORE->m_pMainShader->getProgram(), 1, true);

	//--------------------------------------------------------------
	CORE->drawSkyCube();


	glutSwapBuffers();
}

void Single::reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	CORE->m_tWndSize = { w,h };

	// update proj mat
	CORE->m_mProjMat =
		glm::perspective(glm::radians(45.0f), float(w) / float(h), 0.01f, 300.0f);
	CORE->m_pMainShader->setMat4("projectionTransform", CORE->m_mProjMat);
	CORE->m_pCubeShader->setMat4("projectionTransform", CORE->m_mProjMat);

	//-------------------------------------------------------------------------------------
	//// shadow shader
	//glm::mat4 lightView = glm::lookAt(CORE->m_vLightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//CORE->m_pShadowShader->setMat4("lightSpace", (projectionMat * lightView));
}

void Single::mouseAct(int key, int state, int x, int y)
{
	CORE->m_pScene->mouseActFucn(key, state, { x,y });
	//if (key == GLUT_LEFT_BUTTON) 
}

void Single::mouseMove(int x, int y)
{
	CORE->m_pScene->moveMouse({ x,y });
	CORE->updateViewMat();
}

void Single::mouseMoving(int x, int y)
{
	if (!CORE->m_bHideCursor) return;
	CORE->m_pScene->moveMouse({ x,y }, true);
	CORE->updateViewMat();
}

void Single::mouseWheel(int wheel, int dir, int x, int y)
{
	CORE->m_pScene->scrollMouse(dir);
	CORE->updateViewMat();
}

void Single::keyboardChecker(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':
		glutLeaveMainLoop();
		break;

	case 'f':
	case 'F':
		printf("%f\n", 1.0 / CORE->m_pTimer->getDeltaTime());
		break;

	case 'p':
		glutSetCursor(GLUT_CURSOR_NONE);
		CORE->m_bHideCursor = true;
		break;
	case 'P':
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		CORE->m_bHideCursor = false;
		break;

	case '0':
		CORE->changeScene(0);
		break;
	case '1':
		CORE->changeScene(1);
		break;
	case '2':
		CORE->changeScene(2);
		break;

	}
}

void Single::gameLoop()
{
	float deltaTime = CORE->m_pTimer->getDeltaTime();

	CORE->m_pScene->input();
	CORE->m_pScene->update(deltaTime);
	glutPostRedisplay();			// draw

	CORE->m_pTimer->updateDeltaTime();
}
