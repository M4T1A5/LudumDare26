#include "Character.h"


Character::Character(const sf::Texture& texture)
	: sf::Sprite(texture),
	  _speed(0.0f),
	  _velocity(0.0f, 0.0f) { }

Character::~Character() { }


// Public

void Character::setSpeed(float value)
{
	_speed = value;
}

float Character::getSpeed()
{
	return _speed;
}

void Character::setVelocity(sf::Vector2f value)
{
	_velocity = value;
}

void Character::setVelocity(float x, float y)
{
	_velocity.x = x;
	_velocity.y = y;
}

sf::Vector2f Character::getVelocity()
{
	return _velocity;
}