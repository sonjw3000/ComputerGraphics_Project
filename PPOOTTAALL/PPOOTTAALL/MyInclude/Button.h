#pragma once
#include "Mesh.h"

class TextureClass;

class Button :
    public Mesh
{
private:
	TextureClass* m_pTextures;
	TextureClass* m_pBaseTexture;

private:
	Mesh* m_pBase;

	float m_vMinSize = 0.4f;
	bool m_bPressed = false;
	
	glm::vec3 m_vOriginalScale;

public:
	Button(float size, glm::vec3 pivot);
	~Button();

public:
	void update(float frameTime);
	void draw(unsigned int shaderNum, int textureBind);

	//glm::vec3 getSize() const;

public:
	void setPressState(bool state);
	bool isPressed() const;
};


