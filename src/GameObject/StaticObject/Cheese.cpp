#include "GameObject/StaticObject/Cheese.h"

/*================== Cheese constructor =================*/
Cheese::Cheese(const sf::Sprite& cheese) : InteractableObject::InteractableObject(cheese){}

/*================== handleCollusion =================*/
void Cheese::handleCollusion(GameObject& object)
{
	object.handleCollusion(*this);
}