#include "GameObject/StaticObject/Door.h"

/*================== GameObject constructor =================*/
Door::Door(const sf::Sprite& door) : StaticObject::StaticObject(door), m_removed(false) {}

/*================== removeObject =================*/
/**----------------------------------------------
 * being called from mouse's handleCollusion if the keys counter > 0
 *---------------------------------------------**/
void Door::removeObject()
{
	m_removed = true;
}

/*================== isRemoved =================*/
bool Door::isRemoved() const
{
	return m_removed;
}

/*================== handleCollusion =================*/
void Door::handleCollusion(GameObject& object)
{
	object.handleCollusion(*this);
}