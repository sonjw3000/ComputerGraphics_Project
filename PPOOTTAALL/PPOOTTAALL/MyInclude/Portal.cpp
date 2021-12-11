#include "Portal.h"
#include "TextureClass.h"

//  facing 0 : it's +z, 1 -x, =y, -y, +z, -z
Portal::Portal(float size, int faceNum, glm::vec3 translate) :
	Mesh("Objs/Cube.obj", glm::vec3(0.1f, 4.0f, 2.5f) * size, glm::vec3(0.0f), translate + glm::vec3(0.0f, 2.0f, 0.0f) * size),
	m_pTexture(nullptr),
	m_iFaceNum(faceNum)
{
	glm::vec3 rot(0.0f);
	switch (faceNum) {
	case 0:				// +z
		rot.y = -90.0f;
		break;
	case 1:				// +x
		break;
	case 2:				// -z
		rot.y = 90.0f;
		break;
	case 3:				// -x
		rot.y = 180.0f;
		break;
	case 4:				// -y
		rot.x = 90.0f;
		break;
	case 5:				// +y
		rot.x = -90.0f;
		break;
	default:
		printf("Nan");
	}

	setRotate(rot);

}

Portal::~Portal()
{
	if (m_pTexture) delete m_pTexture;
}

void Portal::draw(unsigned int shaderNum, int bindTex)
{
	if (m_pTexture) m_pTexture->bindTexture(bindTex);

	this->uniformModelingMat(shaderNum);
	Mesh::draw();

#ifdef _DEBUG		// bounding box
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	uniformModelingMat(shaderNum);
	Mesh::draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

#endif

}

glm::vec3 Portal::getScaleVec()
{
	glm::vec3 size = this->getRotateTransform() * glm::vec4(this->m_vScale, 0.0f);
	size = glm::abs(size);


	return size;

}

glm::mat4 Portal::clipProjMat(glm::mat4 const& viewMat, glm::mat4 const& projMat) const
{
	// Oblique View Frustum
	glm::vec4 clipPlane(m_vPivot * glm::vec3(0.0f, 0.0f, -1.0f), glm::length(m_vPivot));
	clipPlane = glm::inverse(glm::transpose(viewMat)) * clipPlane;

	if (clipPlane.w > 0.0f) return viewMat;

	glm::vec4 q = glm::inverse(projMat) * glm::vec4(
		glm::sign(clipPlane.x),
		glm::sign(clipPlane.y),
		1.0f,
		1.0f
	);
	
	glm::vec4 c = clipPlane * (2.0f / (glm::dot(clipPlane, q)));

	glm::mat4 newProj = projMat;
	newProj = glm::row(newProj, 2, c - glm::row(newProj, 3));

	return newProj;
}
