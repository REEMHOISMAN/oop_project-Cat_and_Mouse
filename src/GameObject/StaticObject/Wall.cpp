#include "GameObject/StaticObject/Wall.h"

/*================== Wall constructor =================*/
Wall::Wall(const sf::Sprite& wall): StaticObject::StaticObject(wall){}

/*================== handleCollusion =================*/
void Wall::handleCollusion(GameObject& object)
{
	object.handleCollusion(*this);
}