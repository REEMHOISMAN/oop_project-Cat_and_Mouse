#include "GameObject/StaticObject/InteractableObject.h"

class Cheese : public InteractableObject
{
public:
	Cheese(const sf::Sprite&);
	virtual void handleCollusion(GameObject&) override;
};