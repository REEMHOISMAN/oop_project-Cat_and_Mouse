#pragma once
#include "GameObject/StaticObject/InteractableObject.h"

class LifeGift : public InteractableObject
{
public:
	LifeGift(const sf::Sprite&);
	virtual void handleCollusion(GameObject&) override;
};