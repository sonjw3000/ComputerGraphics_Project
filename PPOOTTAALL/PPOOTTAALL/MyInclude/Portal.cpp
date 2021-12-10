#include "Portal.h"
#include "TextureClass.h"

//  facing 0 : it's +z, 1 -x, =y, -y, +z, -z
Portal::Portal(float size, int faceNum, glm::vec3 translate) :
	Mesh("Objs/Cube.obj", glm::vec3(0.1f, 4.0f, 2.5f) * size, glm::vec3(0.0f), translate + glm::vec3(0.0f, 2.0f, 0.0f) * size),
	m_pTexture(nullptr)
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
		break;
	}

	printf("%d\n", faceNum);
	

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
