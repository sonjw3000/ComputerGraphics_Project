#include "Plane.h"
#include "TextureClass.h"


Plane::Plane(const char* objFile, glm::vec3 s, glm::vec3 r, glm::vec3 t, const char* texFile, bool available) :
	Mesh(objFile, s, r, t),
	m_bAvailable(available)
{
	m_pTexture = new TextureClass(texFile);

	m_vNormal = this->m_mRotate * glm::vec4(m_vNormal, 0.0f);
}

Plane::~Plane()
{
	delete m_pTexture;
}

void Plane::draw(unsigned int shaderNum, int bindTex)
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

glm::vec3 Plane::getScaleVec() const
{
	glm::vec3 size = this->getRotateTransform() * glm::vec4(this->m_vScale, 0.0f);
	size = glm::abs(size);

	return size;
}

glm::vec3 Plane::getNormal() const
{
	return m_vNormal;
}

