#pragma once
#include "GameObject/StaticObject/InteractableObject.h"

class Key : public InteractableObject
{
public:
	Key(const sf::Sprite&);
	virtual void handleCollusion(GameObject&) override;
};