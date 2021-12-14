#include "Button.h"
#include "TextureClass.h"


Button::Button(float size, glm::vec3 pivot) :
	m_vOriginalScale(glm::vec3(0.8f, 0.15f, 0.8f)* size),
	//Mesh("Objs/Cylinder.obj", glm::vec3(0.8f, 0.15f, 0.8f)* size, glm::vec3(0.0f), pivot + glm::vec3(0.0f, 0.075f * size, 0.0f)),
	m_vMinSize(0.075f * size)
{
	m_pTextures = new TextureClass("Texture/Button/button.png");
	m_pBaseTexture = new TextureClass("Texture/Button/buttonBase.png");
	m_pButton = new Mesh("Objs/Cylinder.obj", glm::vec3(0.8f, 0.15f, 0.8f) * size, glm::vec3(0.0f), pivot + glm::vec3(0.0f, 0.075f * size, 0.0f));
	m_pBase = new Mesh("Objs/Cylinder.obj", glm::vec3(1.f, 0.05f, 1.0f) * size, glm::vec3(0.0f), pivot + glm::vec3(0.0f, 0.025f * size, 0.0f));
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
		//glm::vec3 size = m_vScale;
		//glm::vec3 pivot = m_vPivot;
		glm::vec3 size = m_pButton->getScaleVec();
		glm::vec3 pivot = m_pButton->getTranslateVec();
		size.y -= 0.2f * frameTime;
		pivot.y -= 0.1f * frameTime;
		if (size.y <= m_vMinSize) {
			size.y = m_vMinSize;
			pivot.y = m_vMinSize / 2.0f;
		}
		//setScale(size);
		m_pButton->setScale(size);
		//setTranslate(pivot);
		//m_pButton->setTranslate(pivot);
	}
	else {
		/*glm::vec3 size = m_vScale;
		glm::vec3 pivot = m_vPivot;*/
		glm::vec3 size = m_pButton->getScaleVec();
		glm::vec3 pivot = m_pButton->getTranslateVec();
		size.y += 0.2f * frameTime;
		pivot.y += 0.1f * frameTime;
		if (size.y >= m_vOriginalScale.y) {
			size.y = m_vOriginalScale.y;
			pivot.y = m_vOriginalScale.y / 2.0f;
		}
		//setScale(size);
		m_pButton->setScale(size);
		//setTranslate(pivot);
		//m_pButton->setTranslate(pivot);
	}
}

void Button::draw(unsigned int shaderNum, int textureBind)
{
	if (m_pTextures) m_pTextures->bindTexture(textureBind);
	//this->uniformModelingMat(shaderNum);
	
	m_pButton->uniformModelingMat(shaderNum);
	m_pButton->draw();

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

glm::vec3 Button::getButtonTranslateVec() const
{
	return m_pButton->getTranslateVec();
}

glm::vec3 Button::getButtonScaleVec() const
{
	return m_pButton->getScaleVec();
}