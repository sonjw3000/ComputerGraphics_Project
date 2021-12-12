#pragma once
#include "Mesh.h"

class TextureClass;

class Cube : public Mesh {
	TextureClass* m_pTexture;

	glm::vec3 m_vBefMove = glm::vec3(0.0f);
	bool m_bFalling = false;

	float m_fFallingSpeed = 0.0f;

public:
	Cube() = delete;
	Cube(const char* objFile, glm::vec3 s, glm::vec3 r, glm::vec3 t, const char* texFile);
	~Cube();

public:
	void draw(unsigned int shaderNum, int bindTex);
	void update(float deltaTime);

private:
	bool m_bFollowPlayer = false;

public:
	bool isFollowing() const;
	void setFollow(bool flag);

public:
	void moveBack(glm::vec3 backHow);
	void moveLittle(float deltaTime);
};

