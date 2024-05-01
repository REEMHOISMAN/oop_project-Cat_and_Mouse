#include "GameObject/Entity/Entity.h"
#include "GameController.h"
#include <iostream>

/*================== Entity constructor=================*/
Entity::Entity():m_direction(NONE), m_headDirectionLeft(false), m_speed(MOUSE_SPEED), m_startPos(0, 0){}

/*================== Entity constructor=================*/
Entity::Entity(const sf::Sprite& entity, const Directions d,float speed) :
	m_headDirectionLeft(true), m_direction(d), m_speed(speed), m_startPos(0, 0), GameObject::GameObject(entity)
{
	if (d == RIGHT) m_headDirectionLeft = !m_headDirectionLeft;
}
	

/*================== setDirection =================*/
void Entity::setDirection(const Directions d)
{
	m_direction = d;
}

/*================== setSpeed =================*/
void Entity::setSpeed(float speed)
{
	m_speed = speed;
}

/*================== getDirection =================*/
Directions Entity::getDirection()const
{
	return m_direction;
}

/*================== setStartPos =================*/
void Entity::setStartPos(const sf::Vector2f& pos)
{
	m_startPos = pos;
}

/*================== getStartPos =================*/
sf::Vector2f Entity::getStartPos() const
{
	return m_startPos;
}

/*================== move =================*/
void Entity::move(float delta)
{
	sf::Vector2f newPos = getPosition();
	switch (m_direction)
	{
	case LEFT:
		newPos.x -= (m_speed * delta);
		break;

	case RIGHT:
		newPos.x += (m_speed * delta);
		break;

	case UP:
		newPos.y -= (m_speed * delta);
		break;

	case DOWN:
		newPos.y += (m_speed * delta);
		break;
	}

	setPosition(newPos);
	moveHead();
}

/*================== moveHead =================*/
/**----------------------------------------------
 * if the entity walking right but its head direction is left
 * we switch the head direction (same to the oppisite)
 *---------------------------------------------**/
void Entity::moveHead()
{
	if ((m_headDirectionLeft && m_direction == LEFT) || (!m_headDirectionLeft && m_direction == RIGHT))
	{
		auto pos = getPosition();
		scaleSprite({ -1, 1 });
		m_headDirectionLeft = !m_headDirectionLeft;
	}
}