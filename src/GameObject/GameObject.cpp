#include "GameObject/GameObject.h"
#include "GameObject/StaticObject/InteractableObject.h"
#include "GameController.h"

/*================== GameObject constructor =================*/
GameObject::GameObject(const sf::Sprite& object) :m_object(object)
{
	m_object.setOrigin(m_object.getGlobalBounds().width / 2, m_object.getGlobalBounds().height / 2);
}

/*================== drawObject =================*/
void GameObject::drawObject(sf::RenderWindow& window)const
{
	window.draw(m_object);
}

/*================== getPosition =================*/
sf::Vector2f GameObject::getPosition()const
{
	return  m_object.getPosition();
}

/*================== setPosition =================*/
void GameObject::setPosition(const sf::Vector2f& pos)
{
	m_object.setPosition(pos);
}

/*================== getGlobalBounding =================*/
sf::FloatRect GameObject::getGlobalBounding()const
{
	return m_object.getGlobalBounds();
}

/*================== getSprite =================*/
sf::Sprite& GameObject::getSprite()
{
	return m_object;
}

/*================== setSprite =================*/
void GameObject::setSprite(const sf::Sprite& sprite)
{
	m_object = sprite;
}

/*================== scaleSprite =================*/
void GameObject::scaleSprite(const sf::Vector2f& scale)
{
	m_object.scale(scale);
}

/*================== isCollusion =================*/
/**----------------------------------------------
 * this class check object collusion.
 * the Only object that being sent by ref to this function is mouse or one of the gifts
 * if its mouse and its collide with wall, it pushed the mouse a little bit if the
   collusion is not that big
 *---------------------------------------------**/
bool GameObject::isCollusion(GameObject& object, sf::FloatRect& collusionSize)
{
	auto objectRect = object.getGlobalBounding();
	auto pos = object.getPosition();

	if (m_object.getGlobalBounds().intersects(objectRect, collusionSize) )
	{	
		//its gift, so no pushing is needed, just to know that a gift cannot spawn there
		if (dynamic_cast<Mouse*> (&object) == nullptr) return true;
		
		//mouse collide with one of the interactables, not pushing is needed just update the location
		if (dynamic_cast<InteractableObject*> (this) != nullptr)
		{
			object.setPosition(pos);
			return true;
		}
		
		auto direction = ((Mouse&)object).getDirection();
		if (collusionSize.height <= 7)
		{
			direction == UP ? pos.y += collusionSize.height : pos.y -= collusionSize.height;
		}
		if(collusionSize.width <= 7)
		{
			direction == LEFT ? pos.x += collusionSize.width : pos.x -= collusionSize.width;
		}
		object.setPosition(pos);
		return true;
	}
	return false;
}