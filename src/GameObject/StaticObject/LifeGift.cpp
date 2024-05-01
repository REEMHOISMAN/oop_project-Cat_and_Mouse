#include "GameObject/StaticObject/LifeGift.h"

/*================== LifeGift constructor =================*/
LifeGift::LifeGift(const sf::Sprite& gift):InteractableObject::InteractableObject(gift){}

/*================== handleCollusion =================*/
void LifeGift::handleCollusion(GameObject& object)
{
	object.handleCollusion(*this);
}
