#include "Plane.h"
#include "TextureClass.h"

Plane::Plane(const char* objFile, glm::vec3 s, glm::vec3 r, glm::vec3 t, const char* texFile) :
	Mesh(objFile, s, r, t)
{
	m_pTexture = new TextureClass(texFile);
}

Plane::Plane(const char* objFile, glm::vec3 s, glm::vec3 r, glm::vec3 t, const char* texFile,bool available) :
	Mesh(objFile, s, r, t)
{
	m_pTexture = new TextureClass(texFile);
	this->available = available;				// 쏠 수 있는 벽이냐 아니냐
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

