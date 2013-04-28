#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>
#include <TmxLoader.h>
#include "Player.h"
#include "Collision.h"

#include <Thor/Particles.hpp>
#include <Thor/Vectors/PolarVector.hpp>
#include <Thor/Math.hpp>

// Functor that returns the mouse position in float coordinates
struct PlayerPosition
{
	PlayerPosition(Player& player)
	: player(player)
	{
	}

	sf::Vector2f operator() ()
	{
		return player.getPosition() + sf::Vector2f(player.getTextureRect().width / 2, player.getTextureRect().height / 8);
	}

	Player& player;
};

int main()
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	//window.setVerticalSyncEnabled(true);

	// Create a new view("Camera")
	sf::View view = window.getView();
	// Create a rectangle where we store the area of the view to send to the map
	sf::FloatRect viewRectangle;

	// Deltatime stuff
	sf::Clock clock;
	sf::Time dt;

	// Load the map
	tmx::TileMap map;
	map.LoadFromFile("map2.tmx", "assets/");
	Collision::setWorldHitboxes(map.GetSolidObjects());

	// Player
	sf::Texture playerTexture;
	playerTexture.loadFromFile("assets/lanternguy2.png");
	Player player(playerTexture);
	player.setSpeed(10.0f * map.tileWidth());
	player.setPosition(100, 100);

	// Text input
	std::string input;

	// Particle test
	thor::UniversalEmitter::Ptr emitter = thor::UniversalEmitter::create();
	emitter->setEmissionRate(30.f);
	emitter->setParticleLifetime(sf::seconds(1.f));
	emitter->setParticlePosition(PlayerPosition(player));
	
	sf::Texture t;
	t.loadFromFile("assets/particle.png");
	thor::ParticleSystem system(t);
	system.addEmitter(emitter);

	// Build color gradient (green -> teal -> blue)
	thor::ColorGradient gradient = thor::createGradient
	(sf::Color(255, 255, 255)) (1) 
	(sf::Color(242, 255, 48)) (1)
	(sf::Color(183, 8, 8)) (1)
	(sf::Color(0,0,0));

	// Create color and fade in/out animations
	thor::ColorAnimation colorizer(gradient);
	thor::FadeAnimation fader(0.2f, 0.2f);

	// Add particle affectors
	system.addAffector( thor::AnimationAffector::create(colorizer) );
	system.addAffector( thor::AnimationAffector::create(fader) );
	system.addAffector( thor::TorqueAffector::create(100.f) );
	system.addAffector( thor::ForceAffector::create(sf::Vector2f(0.f, 10.f)) );
	system.addAffector( thor::ScaleAffector::create(sf::Vector2f(5.0f, 5.0f)) );

	// Attributes that influence emitter
	thor::PolarVector2f velocity(200.f, -90.f);

	// Main game loop
    while (window.isOpen())
    {
		// Window event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
			if(event.type == sf::Event::TextEntered)
			{
				if(event.text.unicode < 128) // Handle asii chars only
				{
					input += static_cast<char>(event.text.unicode);
				}
				if(event.key.code == sf::Keyboard::Space)
				{
					input = "";
				}
			}

            if (event.type == sf::Event::Closed)
                window.close();
        }

		emitter->setParticleVelocity(thor::Distributions::deflect(velocity, 15.0f));

		system.update(dt);
		
		// Player update
		player.update(dt);
		view.setCenter(player.getPosition().x, player.getPosition().y);

		// Clear the window and set the view("Camera") settings
        window.clear();
		window.setView(view);

		// Map needs to be drawn first

		// Calculate the rectangle of the view so we can limit the map drawing correctly (probably not the best way but it works)
		viewRectangle = sf::FloatRect(view.getCenter().x - view.getSize().x / 2.0f, view.getCenter().y - view.getSize().y / 2.0f,
			view.getSize().x + map.tileWidth() * 3, view.getSize().y + map.tileHeight() * 3);
		map.SetDrawingBounds(viewRectangle); // Acutally set the rectangle
		map.Draw(window); // Now draw the since we know how

		// End of map drawing

		// Add non-map elements below this (e.g. sprites, text, etc..)
		window.draw(player);
		window.draw(system);
		
		if(input == "potato")
		{
			sf::Texture t;
			t.loadFromFile("assets/potato.jpg");
			sf::Sprite potato(t);
			potato.setPosition(player.getPosition().x - potato.getTextureRect().width/2,
				player.getPosition().y - potato.getTextureRect().height/2);
			window.draw(potato);
		}

		// End of draw

		// Display everything
        window.display();

		// Reset clock. Returns time passed since last reset(i.e. deltatime)
		dt = clock.restart();
    }

    return 0;
}