#include "GameObject/StaticObject/FreezeGift.h"

/*================== FreezeGift constructor =================*/
FreezeGift::FreezeGift(const sf::Sprite& gift) :InteractableObject::InteractableObject(gift) {}

/*================== handleCollusion =================*/
void FreezeGift::handleCollusion(GameObject& object)
{
	object.handleCollusion(*this);
}