#include "Collision.h"


// Public

// Static

std::vector<sf::IntRect> Collision::_worldHitboxes;

void Collision::setWorldHitboxes(const std::vector<sf::IntRect> hitboxes)
{
	_worldHitboxes = hitboxes;
}

void Collision::handleWorldCollision(Character& character)
{
	for(size_t i = 0; i < _worldHitboxes.size(); ++i)
	{
		sf::IntRect hitbox = _worldHitboxes[i];
		sf::IntRect objectRect(character.getPosition().x, character.getPosition().y,
			character.getTextureRect().width, character.getTextureRect().height);

		sf::IntRect hitRect;
		if(objectRect.intersects(hitbox, hitRect))
		{
			character.setPosition(character.getPosition().x, character.getPosition().y - hitRect.height + 1);
			character.setVelocity(character.getVelocity().x, 0.0f);
		}
	}

	// TODO: actually handle collisions from all directions
}

bool Collision::onGround(Character& character)
{
	for(size_t i = 0; i < _worldHitboxes.size(); ++i)
	{
		sf::IntRect hitbox = _worldHitboxes[i];
		sf::IntRect objectRect(character.getPosition().x, character.getPosition().y,
			character.getTextureRect().width, character.getTextureRect().height);

		if(objectRect.intersects(hitbox))
		{
			return true;
		}
	}
	
	return false;
}
