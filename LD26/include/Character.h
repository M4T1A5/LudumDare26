#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

class Character : public sf::Sprite
{
public:
	Character(const sf::Texture& texture);
	virtual ~Character();

	void setSpeed(float value);
	float getSpeed();
	void setVelocity(sf::Vector2f value);
	void setVelocity(float x, float y);
	sf::Vector2f getVelocity();

	virtual void update(sf::Time dt) = 0;

protected:
	float _speed;
	sf::Vector2f _velocity;

private:
	Character(const Character& character);
};

#endif