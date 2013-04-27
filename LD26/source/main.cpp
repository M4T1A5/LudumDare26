#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <TmxLoader.h>
#include <iostream>
#include <cmath>

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
	map.LoadFromFile("mmap.tmx", "assets/");

	// Sprite test
	sf::Texture playerTexture;
	playerTexture.loadFromFile("assets/pplayer.png");
	sf::Sprite player(playerTexture);
	player.setPosition(100, 500);

	std::vector<sf::IntRect> hitboxes = map.GetSolidObjects();

    while (window.isOpen())
    {
		// Window event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		// Player movement hacks
		static float speed = 1.0f;
		sf::Vector2f velocity;
		static sf::Vector2f jump;
		static float deacceleration = 0.01f;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && jump.y == 0)
		{
			jump.y = 2.0f;
			deacceleration = 0.01f;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			velocity.x -= ceil(speed * dt.asSeconds());
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			velocity.x += ceil(speed * dt.asSeconds());

		velocity.y -= jump.y;
		jump.y -= deacceleration;

		player.move(velocity.x, velocity.y);

		for(size_t i = 0; i < hitboxes.size(); i++)
		{
			sf::IntRect hitbox = hitboxes[i];

			sf::IntRect playerRect(player.getPosition().x, player.getPosition().y,
				player.getTextureRect().width, player.getTextureRect().height);

			if(playerRect.intersects(hitbox))
			{
				player.setPosition(player.getPosition().x, hitbox.top - player.getTextureRect().height);
				jump.y = 0;
				deacceleration = 0;
			}
		}

		std::cout << "X: " << player.getPosition().x << " Y: " << player.getPosition().y << std::endl;

		view.setCenter(player.getPosition().x, 500 + floor(player.getPosition().y/2.5f));
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