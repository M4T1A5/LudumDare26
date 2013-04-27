#ifndef COLLISION_H_
#define COLLISION_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "Character.h"

// Static class to hanndle gameobject collisions
class Collision
{
public:
	static void setWorldHitboxes(const std::vector<sf::IntRect> hitboxes);

	static void handleWorldCollision(Character& character);

	static bool onGround(Character& character);

private:
	static std::vector<sf::IntRect> _worldHitboxes;

	Collision();
	Collision(const Collision& collision);
	~Collision();	
};

#endif