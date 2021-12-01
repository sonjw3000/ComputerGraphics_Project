#pragma once
#include "Object.h"
#include "Mesh.h"


class TextureClass;

// body is main
class Player : public Mesh {
private:
	TextureClass* m_pTextures[6];

public:
	Player() = delete;
	Player(float size, glm::vec3 pivot);
	~Player();

private:
	bool m_bAlive = false;

public:


private:
	static glm::vec3 m_vDir;
	static glm::vec3 m_vForward;

public:
	static void input(char key);
	void update(float deltaTime);
	void draw(unsigned int shaderNum, int textureBind);

	static void setDirZero();
	static void setForward(glm::vec3 newFow);

public:
	void moveBack(glm::vec3 backHow);

};
