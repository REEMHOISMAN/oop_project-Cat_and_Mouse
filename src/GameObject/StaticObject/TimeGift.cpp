#include "GameObject/StaticObject/TimeGift.h"

/*================== TimeGift constructor =================*/
TimeGift::TimeGift(const sf::Sprite& gift) :InteractableObject::InteractableObject(gift) {}

/*================== handleCollusion =================*/
void TimeGift::handleCollusion(GameObject& object)
{
	object.handleCollusion(*this);
}