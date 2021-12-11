#include "Player.h"
#include "TextureClass.h"


//glm::vec3 Player::m_vDir = glm::vec3(0.0f);
//glm::vec3 Player::m_vForward = glm::vec3(0.0f, 0.0f, 1.0f);

Player::Player(float size, glm::vec3 pivot) :
	Mesh("Objs/Cube.obj", glm::vec3(1.0f) * size, glm::vec3(0.0f), (pivot) + glm::vec3(0.0f, 0.5f, 0.0f) * size),
	m_vRightRot(glm::vec3(0.0f)),
	m_vLeftRot(glm::vec3(0.0f)),
	m_vBackRot(glm::vec3(20.0f,0.0f,0.0f)),
	m_vDir(glm::vec3(0.0f)),
	m_vForward(glm::vec3(0.0f, 0.0f, 1.0f))
{
	m_pBody = new Mesh("Objs/body.obj", glm::vec3(0.125f) * size, glm::vec3(0.0f), pivot + glm::vec3(0.0f, 2.0f, 0.0f) * size);
	m_pLeftLeg = new Mesh("Objs/legLeft.obj", glm::vec3(0.125f) * size, glm::vec3(0.0f), pivot + glm::vec3(0.0f, 2.0f, 0.0f) * size);
	m_pRightLeg = new Mesh("Objs/legRight.obj", glm::vec3(0.125f) * size, glm::vec3(0.0f), pivot + glm::vec3(0.0f, 2.0f, 0.0f) * size);
	m_pBackLeg = new Mesh("Objs/legBack.obj", glm::vec3(0.125f) * size, glm::vec3(0.0f), pivot + glm::vec3(0.0f, 2.0f, 0.0f) * size);
	m_pGun = new Mesh("Objs/potalgun.obj", glm::vec3(0.0625f) * size, glm::vec3(0.0f,180.0f,0.0f), pivot + glm::vec3(-1.5f, 3.5f, 0.0f) * size);

	m_pTextureBody = new TextureClass("Texture/Player/body_texture.jpg");
	m_pTextureLeg = new TextureClass("Texture/Player/leg.png");
}

Player::~Player()
{
	delete m_pTextureBody;
	delete m_pTextureLeg;

	delete m_pBody;
	delete m_pLeftLeg;
	delete m_pRightLeg;
	delete m_pBackLeg;

	delete m_pGun;
}

void Player::input(char key)
{
	static char befKey;

	if (befKey + key == 'w' + 's') {
		befKey = key;
		return;
	}
	befKey = key;

	glm::vec3 dir(0.0f);
	switch (key) {
	case 'w':	dir = m_vForward;	break;
	case 's':	dir = -m_vForward;	break;
	case 'a':	dir = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(m_vForward, 0.0f);		break;
	case 'd':	dir = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(m_vForward, 0.0f);	break;
	}

	m_vDir = glm::normalize(m_vDir + dir);
}

void Player::update(float deltaTime)
{
	static float fMoveSpeed = 5.0f;
	static float fGravity = 35.28f;			// 9.8m/s * 60 * 60 / 1000
	static float fRotateSpeed = 72000.0f;
	static bool bIncreaseFront = true;
	static bool bIncreaseBack = false;

	// gravity
	//if (m_bJump || m_bFalling) {
	//	printf("pos : %.2f\tspeed : %.2f\n", this->m_vPivot.y, m_fFallingSpeed);
	//}
	glm::vec3 offset = m_vDir;
	offset.x *= fMoveSpeed * deltaTime;
	offset.y += m_fFallingSpeed * deltaTime;
	offset.z *= fMoveSpeed * deltaTime;

	m_fFallingSpeed -= fGravity * deltaTime;
	if (m_fFallingSpeed <= -216.0f) m_fFallingSpeed = -216.0f;		// terminal falling speed
	if (m_bJump && !m_bFalling && m_fFallingSpeed <= 0.0f) m_bFalling = true;

	//glm::vec3 offset = m_vDir * fMoveSpeed * deltaTime;
	this->setTranslate(m_vPivot + offset);



	// if moved
	float rotSpeed = fRotateSpeed * deltaTime;
	if (m_vDir.x + m_vDir.z != 0) {
		m_vRightRot.x += (1 - 2 * bIncreaseFront) * deltaTime * rotSpeed;
		m_vLeftRot.x -= (1 - 2 * bIncreaseFront) * deltaTime * rotSpeed;
		m_vBackRot.x += (1 - 2 * bIncreaseBack) * deltaTime * rotSpeed;

		if (abs(m_vLeftRot.x) >= 30.0f) {
			bIncreaseFront = !bIncreaseFront;
			m_vRightRot.x += (1 - 2 * bIncreaseFront) * deltaTime * rotSpeed;
			m_vLeftRot.x -= (1 - 2 * bIncreaseFront) * deltaTime * rotSpeed;
		}

		if (abs(m_vBackRot.x) >= 30.0f) {
			bIncreaseBack = !bIncreaseBack;
			m_vBackRot.x += (1 - 2 * bIncreaseBack) * deltaTime * rotSpeed;
		}
	}
	// if not moved stop 
	else {
		if (m_vLeftRot.x > 0.1f) {
			m_vLeftRot.x -= deltaTime * rotSpeed;
			m_vRightRot.x += deltaTime * rotSpeed;
			if (m_vLeftRot.x <= 0.1f) {
				m_vLeftRot.x = 0;
				m_vRightRot.x = 0;
			}
		}
		else if (m_vLeftRot.x < -0.1f) {
			m_vLeftRot.x += deltaTime * rotSpeed;
			m_vRightRot.x -= deltaTime * rotSpeed;
			if (m_vLeftRot.x >= -0.1f) {
				m_vLeftRot.x = 0;
				m_vRightRot.x = 0;
			}
		}

		if (m_vBackRot.x > 0.1f) {
			m_vBackRot.x -= deltaTime * rotSpeed;
			if (m_vBackRot.x <= 0.1f) m_vBackRot.x = 0;
		}
		else if (m_vBackRot.x < -0.1f) {
			m_vBackRot.x += deltaTime * rotSpeed;
			if (m_vBackRot.x >= 0.1f) m_vBackRot.x = 0;
		}
	}

	m_pLeftLeg->setRotate(m_vLeftRot);
	m_pRightLeg->setRotate(m_vRightRot);
	m_pBackLeg->setRotate(m_vBackRot);
}

void Player::draw(unsigned int shaderNum, int textureBind)
{
	// texture


	//this->uniformModelingMat(shaderNum);
	glm::mat4 modeling(1.0f);

	m_pTextureBody->bindTexture(textureBind);

	// body
	modeling = this->m_mSRTModel * m_pBody->getModelTransform();
	glUniformMatrix4fv(glGetUniformLocation(shaderNum, "modelTransform"), 1, GL_FALSE, glm::value_ptr(modeling));
	m_pBody->draw();

	m_pTextureLeg->bindTexture(textureBind);

	// l leg
	modeling = this->m_mSRTModel * m_pLeftLeg->getModelTransform();
	glUniformMatrix4fv(glGetUniformLocation(shaderNum, "modelTransform"), 1, GL_FALSE, glm::value_ptr(modeling));
	m_pLeftLeg->draw();

	// r leg
	modeling = this->m_mSRTModel * m_pRightLeg->getModelTransform();
	glUniformMatrix4fv(glGetUniformLocation(shaderNum, "modelTransform"), 1, GL_FALSE, glm::value_ptr(modeling));
	m_pRightLeg->draw();

	// b leg
	modeling = this->m_mSRTModel * m_pBackLeg->getModelTransform();
	glUniformMatrix4fv(glGetUniformLocation(shaderNum, "modelTransform"), 1, GL_FALSE, glm::value_ptr(modeling));
	m_pBackLeg->draw();

	modeling = this->m_mSRTModel * m_pGun->getModelTransform();
	glUniformMatrix4fv(glGetUniformLocation(shaderNum, "modelTransform"), 1, GL_FALSE, glm::value_ptr(modeling));
	m_pGun->draw();


#ifdef _DEBUG		// bounding box
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	uniformModelingMat(shaderNum);
	Mesh::draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

#endif
}

void Player::setDirZero()
{
	m_vDir = glm::vec3(0.0f);
}

void Player::setForward(glm::vec3 newFow)
{
	m_vForward = newFow;
}

void Player::setDir(glm::vec3 dir)
{
	m_vDir = dir;
}

glm::vec3 Player::getFoward() const 
{
	return m_vForward;
}

glm::vec3 Player::getDir() const
{
	return m_vDir;
}

void Player::moveBack(glm::vec3 backHow)
{
	if (backHow.y != 0.0f) {
		m_bJump = false;
		m_bFalling = false;
		m_fFallingSpeed = 0.0f;
	}

	glm::vec3 temp(m_vDir.x != 0, m_vDir.y != 0, m_vDir.z != 0);

	backHow = backHow * temp;

	this->setTranslate(m_vPivot - backHow);
}

void Player::moveLittle(float deltaTime)
{
	//m_vPivot += m_vForward;
	setTranslate(m_vPivot + m_vDir * deltaTime);
}

void Player::setJump()
{
	if (m_bJump) return;
	m_bJump = true;
	m_bFalling = false;
	m_fFallingSpeed = 11.2f;
}

