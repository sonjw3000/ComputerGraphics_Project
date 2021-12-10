#pragma once
#include "Mesh.h"

class TextureClass;


class Portal :
    public Mesh
{
private:
	TextureClass* m_pTexture;

private:
	CameraVectors m_tCameraVectors;

public:
	Portal() = delete;
	Portal(float size, int faceNum, glm::vec3 translate);
	~Portal();

public:
	void draw(unsigned int shaderNum, int bindTex);

public:
	glm::mat4 getPortalView(glm::mat4& originView, glm::vec3 from);

};

