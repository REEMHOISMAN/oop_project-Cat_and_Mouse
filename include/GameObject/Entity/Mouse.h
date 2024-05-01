#pragma once
#include "GameObject/Entity/Entity.h"

class GameController;
class Level;

class Mouse : public Entity
{
public:
	Mouse(GameController&, Level&);

	void setDirections();
	int getScore()const;
	void setScore(int);
	int getLives()const;
	void resetKeys();
	int getKeys()const;
	void resetMouse();
	void runOutOfTime();

	virtual void handleCollusion(GameObject&) override;
	virtual void handleCollusion(Cheese&)override;
	virtual void handleCollusion(Key&)override;
	virtual void handleCollusion(Door&) override;
	virtual void handleCollusion(LifeGift&)override;
	virtual void handleCollusion(PopCatGift&)override;
	virtual void handleCollusion(FreezeGift&)override;
	virtual void handleCollusion(TimeGift&)override;
	virtual void handleCollusion(Cat&)override;

private:
	int m_lives;
	int m_keys;
	int m_score;
	GameController& m_game;
	Level& m_level;
};