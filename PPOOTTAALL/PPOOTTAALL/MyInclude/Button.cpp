#include "Button.h"
#include "TextureClass.h"


Button::Button(float size, glm::vec3 pivot) :
	m_vOriginalScale(glm::vec3(1.0f)* size),
	Mesh("Objs/Cube.obj", glm::vec3(1.0f) * size, glm::vec3(0.0f), pivot + glm::vec3(0.0f, 0.5f * size, 0.0f))
{
	m_pTextures = new TextureClass("Texture/Button/button.png");
	m_pBaseTexture = new TextureClass("Texture/Button/buttonBase.png");

	m_pBase = new Mesh("Objs/Cube.obj", glm::vec3(2.0f, 0.3f, 2.0f) * size, glm::vec3(0.0f), pivot + glm::vec3(0.0f, 0.15f * size, 0.0f));
}

Button::~Button()
{
	delete m_pTextures;
	delete m_pBaseTexture;
	delete m_pBase;
}

void Button::update(float frameTime)
{
	if (m_bPressed) {
		glm::vec3 size = m_vScale;
		glm::vec3 pivot = m_vPivot;
		size.y -= 2.0f * frameTime;
		pivot.y -= 1.0f * frameTime;
		if (size.y <= m_vMinSize) {
			size.y = m_vMinSize;
			pivot.y = m_vMinSize / 2.0f;
		}
		setScale(size);
		setTranslate(pivot);
	}
	else {
		glm::vec3 size = m_vScale;
		glm::vec3 pivot = m_vPivot;
		size.y += 2.0f * frameTime;
		pivot.y += 1.0f * frameTime;
		if (size.y >= m_vOriginalScale.y) {
			size.y = m_vOriginalScale.y;
			pivot.y = m_vOriginalScale.y / 2.0f;
		}
		setScale(size);
		setTranslate(pivot);
	}
}

void Button::draw(unsigned int shaderNum, int textureBind)
{
	if (m_pTextures) m_pTextures->bindTexture(textureBind);
	this->uniformModelingMat(shaderNum);
	Mesh::draw();

	if (m_pBaseTexture) m_pBaseTexture->bindTexture(textureBind);
	m_pBase->uniformModelingMat(shaderNum);
	m_pBase->draw();
}

//glm::vec3 Button::getSize() const
//{
//	return m_vOriginalScale;
//}

void Button::setPressState(bool state)
{
	m_bPressed = state;
}

bool Button::isPressed() const
{
	return m_bPressed;
}