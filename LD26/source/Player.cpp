#include "Player.h"


Player::Player(const sf::Texture& texture)
	: Character(texture)
{
	initAnimations();
}

Player::~Player() { }


// Public

void Player::update(sf::Time dt)
{
	handleInput();
	updateAnimation();

	_velocity.y += 0.5f;
	//_velocity.x += -_velocity.x*dt.asSeconds()*15;

	move(_velocity * dt.asSeconds()); // Function of the sprite class

	animator.update(dt);
	animator.animate(*this);

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

void Player::initAnimations()
{
	thor::FrameAnimation idle;
	addFrames(idle, 0, 1, 0, 56, 64);
	addFrames(idle, 0, 1, 1, 56, 64);
	addAnimation(idle, "idle", sf::seconds(2.0f));

	thor::FrameAnimation walkRight;
	addFrames(walkRight, 0, 5, 0, 56, 64);
	addAnimation(walkRight, "walkRight", sf::seconds(0.5f));

	thor::FrameAnimation walkLeft;
	addFrames(walkLeft, 0, 5, 1, 56, 64);
	addAnimation(walkLeft, "walkLeft", sf::seconds(0.5f));

	animator.playAnimation("idle");
}

void Player::updateAnimation()
{
	if(!animator.isPlayingAnimation())
		animator.playAnimation("idle");
	else if(_velocity.x > 0 && animator.getPlayingAnimation() != "walkRight")
		animator.playAnimation("walkRight");
	else if(_velocity.x < 0 && animator.getPlayingAnimation() != "walkLeft")
		animator.playAnimation("walkLeft");
	
}