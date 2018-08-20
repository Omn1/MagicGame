#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include "Object.h"
#include "DynamicObject.h"
#include "Player.h"
#include "Misc.h"
#include "World.h"





World world;




class House : public DynamicObject {
public:
	House()
	{
		animationLength = 3;
	}
	std::string getSpriteName(float interactTime)
	{
		animationTime += interactTime;
		if (animationTime >= timeForNewSprite)
		{
			animationTime = 0;
			currentSpriteNum++;
			if (currentSpriteNum > animationLength)
			{
				currentSpriteNum = 1;
			}
		}
		return "house" + std::to_string(currentSpriteNum);
	}
};







int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	sf::View mainView(window.getDefaultView());

	sf::Clock clock;

	world.worldRect = sf::FloatRect(0, 0, 1280, 720);

	while (window.isOpen())
	{
		// Track time
		float interactTime = (float)clock.getElapsedTime().asMicroseconds()/1000.0f;
		//std::cout << interactTime << std::endl;
		clock.restart();

		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if(event.type == sf::Event::Resized)
				window.setView(mainView = sf::View(sf::FloatRect(0.f, 0.f,
					static_cast<float>(window.getSize().x),
					static_cast<float>(window.getSize().y))));
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Return) {
					world.player->handleSpellCast((sf::Vector2f)sf::Mouse::getPosition(window));
				}
			}
		}
		world.player->handleInput();
		
		// Iterate
		//world.player->move(interactTime);
		world.updateObjects(interactTime);
		// Draw
		window.clear(sf::Color(255, 255, 255));
		world.draw(window,interactTime);
		window.display();
	}

	return 0;
}