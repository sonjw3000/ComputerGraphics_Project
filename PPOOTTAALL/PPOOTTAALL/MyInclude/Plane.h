#pragma once
#include "Mesh.h"

class TextureClass;

class Plane : public Mesh {
	TextureClass* m_pTexture;
	bool available;
public:
	Plane() = delete;
	Plane(const char* objFile, glm::vec3 s, glm::vec3 r, glm::vec3 t, const char* texFile);
	Plane(const char* objFile, glm::vec3 s, glm::vec3 r, glm::vec3 t, const char* texFile, bool available);
	~Plane();

public:
	void draw(unsigned int shaderNum, int bindTex);	
};

