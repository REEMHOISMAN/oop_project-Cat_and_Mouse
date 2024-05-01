#pragma once
#include "GameObject/StaticObject/StaticObject.h"

class InteractableObject : public StaticObject
{
public:
	InteractableObject() = default;
	InteractableObject(const sf::Sprite&);
	virtual void handleCollusion(GameObject&) = 0;
};