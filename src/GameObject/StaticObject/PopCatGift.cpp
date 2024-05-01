#include "GameObject/StaticObject/PopCatGift.h"

/*================== PopCatGift constructor =================*/
PopCatGift::PopCatGift(const sf::Sprite& gift) :InteractableObject::InteractableObject(gift) {}

/*================== handleCollusion =================*/
void PopCatGift::handleCollusion(GameObject& object)
{
	object.handleCollusion(*this);
}