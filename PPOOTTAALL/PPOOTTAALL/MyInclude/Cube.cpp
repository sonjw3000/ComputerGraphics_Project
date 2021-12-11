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

	glm::vec3 offset = m_vDir;
	offset.x *= fMoveSpeed * deltaTime;
	offset.y += m_fFallingSpeed * deltaTime;
	offset.z *= fMoveSpeed * deltaTime;

	m_fFallingSpeed -= fGravity * deltaTime;
	if (m_fFallingSpeed <= -216.0f) m_fFallingSpeed = -216.0f;		// terminal falling speed
	if (m_bJump && !m_bFalling && m_fFallingSpeed <= 0.0f) m_bFalling = true;

	//glm::vec3 offset = m_vDir * fMoveSpeed * deltaTime;
	this->setTranslate(m_vPivot + offset);
}