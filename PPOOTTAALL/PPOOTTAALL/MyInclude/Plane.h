#pragma once
#include "Mesh.h"

class TextureClass;

class Plane : public Mesh {
	TextureClass* m_pTexture;
	bool m_bAvailable;
public:
	Plane() = delete;
	Plane(const char* objFile, glm::vec3 s, glm::vec3 r, glm::vec3 t, const char* texFile, bool available = false);
	~Plane();

public:
	void draw(unsigned int shaderNum, int bindTex);	

public:
	glm::vec3 getScaleVec() const;

private:
	glm::vec3 m_vNormal = glm::vec3(0.0f, 1.0f, 0.0f);

public:
	glm::vec3 getNormal() const;
};

