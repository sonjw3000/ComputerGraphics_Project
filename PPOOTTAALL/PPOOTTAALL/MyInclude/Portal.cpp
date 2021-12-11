#include "Portal.h"
#include "TextureClass.h"

//  facing 0 : it's +z, 1 -x, =y, -y, +z, -z
Portal::Portal(float size, int faceNum, glm::vec3 translate) :
	Mesh("Objs/Cube.obj", glm::vec3(0.1f, 4.0f, 2.5f) * size, glm::vec3(0.0f), translate + glm::vec3(0.0f, 2.0f, 0.0f) * size),
	m_pTexture(nullptr),
	m_iFaceNum(faceNum)
{
	//glm::vec3 newSize(0.1f, 4.0f, 2.5f);
	//switch (m_iFaceNum) {
	//case 0:				// +z
	//	newSize = glm::vec3(2.5f, 4.0f, 0.1f);
	//	break;
	//case 1:				// +x
	//	break;
	//case 2:				// -z
	//	newSize = glm::vec3(2.5f, 4.0f, 0.1f);
	//	break;
	//case 3:				// -x
	//	break;
	//case 4:				// -y
	//	newSize = glm::vec3(2.5f, 0.1f, 4.0f);
	//	break;
	//case 5:				// +y
	//	newSize = glm::vec3(2.5f, 0.1f, 4.0f);
	//	break;
	//default:
	//	printf("Nan");
	//	break;
	//}

	//printf("%d\n", faceNum);
	//printf("%.2f, %.2f, %.2f\n", newSize.x, newSize.y, newSize.z);

	//setScale(newSize * size);

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
