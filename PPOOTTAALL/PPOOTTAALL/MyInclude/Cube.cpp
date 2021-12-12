#include "Cube.h"
#include "TextureClass.h"

Cube::Cube(const char* objFile, glm::vec3 s, glm::vec3 r, glm::vec3 t, const char* texFile) :
	Mesh(objFile, s, r, t)
{
	m_pTexture = new TextureClass(texFile);
}

Cube::~Cube()
{
	delete m_pTexture;
}

void Cube::draw(unsigned int shaderNum, int bindTex)
{
	m_pTexture->bindTexture(bindTex);
	this->uniformModelingMat(shaderNum);
	Mesh::draw();

#ifdef _DEBUG		// bounding box
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	uniformModelingMat(shaderNum);
	Mesh::draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

#endif
}

void Cube::update(float deltaTime) {
	static float fMoveSpeed = 5.0f;
	static float fGravity = 35.28f;			// 9.8m/s * 60 * 60 / 1000

	glm::vec3 offset(0.0f);
	offset.y += m_fFallingSpeed * deltaTime;

	m_fFallingSpeed -= fGravity * deltaTime;
	if (m_fFallingSpeed <= -216.0f) m_fFallingSpeed = -216.0f;		// terminal falling speed

	//glm::vec3 offset = m_vDir * fMoveSpeed * deltaTime;
	this->setTranslate(m_vPivot + offset);

	m_vBefMove = offset;
}

void Cube::moveBack(glm::vec3 backHow)
{
	if (backHow.y != 0.0f) {
		m_bFalling = false;
		m_fFallingSpeed = 0.0f;
	}

	backHow = backHow * m_vBefMove;

	this->setTranslate(m_vPivot - backHow);
}
