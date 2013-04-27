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


// Protected

// Adds a range of frames, assuming they are aligned as rectangles in the texture.
// animation:      FrameAnimation to modify
// x:              Column index of the texture rectangle
// [yFirst,yLast]: Bounds for row indices (if yLast < yFirst, add frames in reverse order)
// duration:       Relative duration of current frame (1 by default)
void Character::addFrames(thor::FrameAnimation& animation, int xFirst, int xLast, int y, int frameWidth, int frameHeight, float duration)
{
	const int step = (xFirst < xLast) ? +1 : -1;
	xLast += step; // so yLast is excluded in the range

	for (int x = xFirst; x != xLast; x += step)
		animation.addFrame(duration, sf::IntRect(frameWidth*x, frameHeight*y, frameWidth, frameHeight));
}

void Character::addAnimation(thor::FrameAnimation& animation, std::string id, sf::Time duration)
{
	animations.push_back(animation);
	animator.addAnimation(id, *--animations.end(), duration);
}