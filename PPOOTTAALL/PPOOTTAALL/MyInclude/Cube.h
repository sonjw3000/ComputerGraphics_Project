#pragma once
#include "Mesh.h"

class TextureClass;

class Cube : public Mesh {
	TextureClass* m_pTexture;
	glm::vec3 m_vDir;
	glm::vec3 m_vForward;
	bool m_bJump = false;
	bool m_bFalling = false;
	float m_fFallingSpeed = 0.0f;
public:
	Cube() = delete;
	Cube(const char* objFile, glm::vec3 s, glm::vec3 r, glm::vec3 t, const char* texFile);
	~Cube();

public:
	void draw(unsigned int shaderNum, int bindTex);
	void update(float deltaTime);
};

