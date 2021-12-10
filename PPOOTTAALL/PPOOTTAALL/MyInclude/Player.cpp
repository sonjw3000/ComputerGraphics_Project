#include "Player.h"
#include "TextureClass.h"


glm::vec3 Player::m_vDir = glm::vec3(0.0f);
glm::vec3 Player::m_vForward = glm::vec3(0.0f, 0.0f, 1.0f);

Player::Player(float size, glm::vec3 pivot) :
	Mesh("Objs/Cube.obj", glm::vec3(1.0f) * size, glm::vec3(0.0f), (pivot)+glm::vec3(0.0f, 0.5f, 0.0f) * size)
{
	m_pBody = new Mesh("Objs/body.obj", glm::vec3(0.125f) * size, glm::vec3(0.0f), pivot + glm::vec3(0.0f, 1.5f, 0.0f) * size);
	m_pLeftLeg = new Mesh("Objs/legLeft.obj", glm::vec3(0.125f) * size, glm::vec3(0.0f), pivot + glm::vec3(0.0f, 1.5f, 0.0f) * size);
	m_pRightLeg = new Mesh("Objs/legRight.obj", glm::vec3(0.125f) * size, glm::vec3(0.0f), pivot + glm::vec3(0.0f, 1.5f, 0.0f) * size);
	m_pBackLeg = new Mesh("Objs/legBack.obj", glm::vec3(0.125f) * size, glm::vec3(0.0f), pivot + glm::vec3(0.0f, 1.5f, 0.0f) * size);

	m_pTextureBody = new TextureClass("Texture/Player/body_texture.jpg");
	//m_pTextureLeg = new TextureClass("Texture/Player/leg_texture.jpg");
}

Player::~Player()
{
	delete m_pTextureBody;
	delete m_pTextureLeg;

	delete m_pBody;
	delete m_pLeftLeg;
	delete m_pRightLeg;
	delete m_pBackLeg;
}

void Player::input(char key)
{
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

	glm::vec3 offset = m_vDir * fMoveSpeed * deltaTime;
	this->setTranslate(m_vPivot + offset);
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
	//Mesh::draw();
}

void Player::setDirZero()
{
	m_vDir = glm::vec3(0.0f);
}

void Player::setForward(glm::vec3 newFow)
{
	m_vForward = newFow;
}

void Player::moveBack(glm::vec3 backHow)
{
	this->setTranslate(m_vPivot - backHow);
}



