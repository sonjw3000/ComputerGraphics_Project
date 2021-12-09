#include "Portal.h"
#include "TextureClass.h"

//  facing 0 : it's +x, 1 -x, =y, -y, +z, -z
Portal::Portal(float size, int faceNum, glm::vec3 translate) :
	Mesh("Objs/Cube.obj", glm::vec3(0.1f, 2.0f, 1.0f) * size, glm::vec3(0.0f), translate + glm::vec3(0.0f, 1.0f, 0.0f) * size)
{
	//glm::vec3 rot(0.0f);
	//switch (faceNum) {
	//case 1: 
	//	rot.y = 90.0f;
	//	break;
	//case 2:
	//	
	//}

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

}
