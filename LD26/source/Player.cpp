#include "Player.h"


Player::Player(const sf::Texture& texture)
	: Character(texture) { }

Player::~Player() { }


// Public

void Player::update(sf::Time dt)
{
	handleInput();

	_velocity.y += 0.5f;
	//_velocity.x += -_velocity.x*dt.asSeconds()*15;

	move(_velocity * dt.asSeconds()); // Function of the sprite class

	Collision::handleWorldCollision(*this);
}


// Private

void Player::handleInput()
{
	// Side to side movement
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_velocity.x = -_speed;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_velocity.x = _speed;
	}
	else
	{
		_velocity.x = 0;
	}

	// Jumping
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Collision::onGround(*this))
	{
		_velocity.y = -_speed;
	}
}