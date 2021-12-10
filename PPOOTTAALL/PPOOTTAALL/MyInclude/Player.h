#pragma once
#include "Object.h"
#include "Mesh.h"


class TextureClass;

// body is main
class Player : public Mesh {
private:
	// body
	TextureClass* m_pTextureBody;
	TextureClass* m_pTextureLeg;

	Mesh* m_pBody;
	Mesh* m_pLeftLeg;
	Mesh* m_pRightLeg;
	Mesh* m_pBackLeg;

	Mesh* m_pGun;
public:
	Player() = delete;
	Player(float size, glm::vec3 pivot);
	~Player();

private:
	bool m_bAlive = false;

public:

private:
	glm::vec3 m_vLeftRot;
	glm::vec3 m_vRightRot;
	glm::vec3 m_vBackRot;

private:
	glm::vec3 m_vDir;
	glm::vec3 m_vForward;

public:
	void input(char key);
	void update(float deltaTime);
	void draw(unsigned int shaderNum, int textureBind);

	void setDirZero();
	void setDir(glm::vec3 newFow);
	void setForward(glm::vec3 newFow);

	glm::vec3 getDir() const;
	glm::vec3 getFoward() const;

public:
	void moveBack(glm::vec3 backHow);
	void moveLittle(float deltaTime);

};

