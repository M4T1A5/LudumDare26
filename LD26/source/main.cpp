#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>
#include <TmxLoader.h>
#include "Player.h"
#include "Collision.h"

int main()
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

	// Create a new view("Camera")
	sf::View view = window.getView();
	// Create a rectangle where we store the area of the view to send to the map
	sf::FloatRect viewRectangle;

	// Deltatime stuff
	sf::Clock clock;
	sf::Time dt;

	// Load the map
	tmx::TileMap map;
	map.LoadFromFile("Testmap.tmx", "assets/");
	Collision::setWorldHitboxes(map.GetSolidObjects());

	// Player
	sf::Texture playerTexture;
	playerTexture.loadFromFile("assets/lanternguy.png");
	Player player(playerTexture);
	player.setSpeed(10.0f * map.tileWidth());
	player.setPosition(100, 100);

	// Main game loop
    while (window.isOpen())
    {
		// Window event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		player.update(dt);

		view.setCenter(player.getPosition().x, player.getPosition().y);
		// End of camera movement hacks

		// Clear the window and set the view("Camera") settings
        window.clear();
		window.setView(view);

		// Map needs to be drawn first

		// Calculate the rectangle of the view so we can limit the map drawing correctly (probably not the best way but it works)
		viewRectangle = sf::FloatRect(view.getCenter().x - view.getSize().x / 2.0f, view.getCenter().y - view.getSize().y / 2.0f,
			view.getSize().x, view.getSize().y);
		map.SetDrawingBounds(viewRectangle); // Acutally set the rectangle
		map.Draw(window); // Now draw the since we know how

		// End of map drawing

		// Add non-map elements below this (e.g. sprites, text, etc..)
		window.draw(player);
		
		// End of draw

		// Display everything
        window.display();

		// Reset clock. Returns time passed since last reset(i.e. deltatime)
		dt = clock.restart();
    }

    return 0;
}