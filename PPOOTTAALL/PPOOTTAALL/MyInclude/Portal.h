#pragma once
#include "Mesh.h"

class TextureClass;


class Portal :
    public Mesh
{
	TextureClass* m_pTexture;
	int m_iFaceNum;

public:
	Portal() = delete;
	Portal(float size, int faceNum, glm::vec3 translate);
	~Portal();

public:
	void draw(unsigned int shaderNum, int bindTex);
	glm::vec3 getScaleVec();

	glm::mat4 clipProjMat(glm::mat4 const& viewMat, glm::mat4 const& projMat) const;
};

