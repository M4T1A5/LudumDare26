#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Character.h"
#include "Collision.h"
#include <Thor/Particles.hpp>

class Player : public Character
{
public:
	Player(const sf::Texture& texture);
	~Player();

	void update(sf::Time dt);

private:
	float _jumpForce;

	void handleInput();

	void initAnimations();

	void updateAnimation();

};

#endif
