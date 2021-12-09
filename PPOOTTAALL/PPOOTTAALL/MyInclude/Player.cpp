#include "Player.h"
#include "TextureClass.h"


glm::vec3 Player::m_vDir = glm::vec3(0.0f);
glm::vec3 Player::m_vForward = glm::vec3(0.0f, 0.0f, 1.0f);

Player::Player(float size, glm::vec3 pivot) :
	Mesh("Objs/Cube.obj", glm::vec3(1.0f, 1.0f, 1.0f)* size, glm::vec3(0.0f), (pivot)+glm::vec3(0.0f, 0.5f, 0.0f) * size)
{
	body = new Mesh("Objs/body.obj", glm::vec3(0.125f, 0.125f, 0.125f) * size, glm::vec3(0.0f), (pivot)+glm::vec3(0.0f, 1.5f, 0.0f) * size);
	leftLeg = new Mesh("Objs/legLeft.obj", glm::vec3(0.125f, 0.125f, 0.125f) * size, glm::vec3(0.0f), (pivot)+glm::vec3(0.0f, 1.5f, 0.0f) * size);
	rightLeg = new Mesh("Objs/legRight.obj", glm::vec3(0.125f, 0.125f, 0.125f) * size, glm::vec3(0.0f), (pivot)+glm::vec3(0.0f, 1.5f, 0.0f) * size);
	backLeg = new Mesh("Objs/legBack.obj", glm::vec3(0.125f, 0.125f, 0.125f) * size, glm::vec3(0.0f), (pivot)+glm::vec3(0.0f, 1.5f, 0.0f) * size);
	for (int i = 0; i < 0; ++i) {
		m_pTextures[i] = new TextureClass("");
	}
}

Player::~Player()
{
	delete[] body;
	delete[] m_pTextures;
	delete[] leftLeg;
	delete[] rightLeg;
	delete[] backLeg;
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

	this->uniformModelingMat(shaderNum);
	body->draw();
	leftLeg->draw();
	rightLeg->draw();
	backLeg->draw();
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



