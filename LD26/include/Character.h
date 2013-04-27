#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <Thor/Animation.hpp>
#include <string>
#include <vector>

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
	std::vector<thor::FrameAnimation> animations;
	thor::Animator<sf::Sprite, std::string> animator;

	void addFrames(thor::FrameAnimation& animation, int xFirst, int xLast, int y, int frameWidth, int frameHeight, float duration = 1.0f);
	void addAnimation(thor::FrameAnimation& animation, std::string id, sf::Time duration);

private:
	Character(const Character& character);
};

#endif