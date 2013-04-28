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
	sf::IntRect characterRect(character.getPosition().x, character.getPosition().y,
			character.getTextureRect().width, character.getTextureRect().height);

	for(size_t i = 0; i < _worldHitboxes.size(); ++i)
	{
		sf::IntRect hitbox = _worldHitboxes[i];

		sf::IntRect hitRect;
		if(characterRect.intersects(hitbox, hitRect))
		{
			// The constants are needed to stop the vibration effect

			// Top or Bottom collision
			if(hitRect.width > hitRect.height)
			{
				// Character bottom hits hitbox top
				if(characterRect.top < (hitbox.top + hitbox.height) && characterRect.top > hitbox.top) 
				{
					character.setPosition(character.getPosition().x, character.getPosition().y + hitRect.height + 1);
					character.setVelocity(character.getVelocity().x, 0.0f);
				}
				// Character top hits hitbox bottom
				else
				{
					character.setPosition(character.getPosition().x, character.getPosition().y - hitRect.height + 0.7f);
					character.setVelocity(character.getVelocity().x, 0.0f);
				}
			}
			// Left or Right collision
			else
			{
				// Character left hits hitbox right
				if(characterRect.left < (hitbox.left + hitbox.width) && characterRect.left > hitbox.left)
				{
					character.setPosition(character.getPosition().x + hitRect.width - 0.5f, character.getPosition().y);
					character.setVelocity(0.0f, character.getVelocity().y);
				}
				else
				{
					character.setPosition(character.getPosition().x - hitRect.width + 0.5f, character.getPosition().y);
					character.setVelocity(0.0f, character.getVelocity().y);
				}
			}
		}
	}
}

bool Collision::onGround(Character& character)
{
	for(size_t i = 0; i < _worldHitboxes.size(); ++i)
	{
		sf::IntRect hitbox = _worldHitboxes[i];
		sf::IntRect characterRect(character.getPosition().x, character.getPosition().y,
			character.getTextureRect().width, character.getTextureRect().height + 1);

		sf::IntRect hitRect;
		if(characterRect.intersects(hitbox, hitRect))
		{
			if(hitRect.width > 1)	// Check if the hit width is greater than 1 pixel
				return true;		// This means you are on the ground and not only againts a wall
		}
	}
	
	return false;
}
