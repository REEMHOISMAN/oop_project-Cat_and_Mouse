#pragma once
#include "GameObject/StaticObject/InteractableObject.h"

class FreezeGift : public InteractableObject
{
public:
	FreezeGift(const sf::Sprite&);
	virtual void handleCollusion(GameObject&) override;
};