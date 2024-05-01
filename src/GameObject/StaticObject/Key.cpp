#include "GameObject/StaticObject/Key.h"

/*================== Key constructor =================*/
Key::Key(const sf::Sprite& key) : InteractableObject::InteractableObject(key) {}

/*================== handleCollusion =================*/
void Key::handleCollusion(GameObject& object)
{
	object.handleCollusion(*this);
}