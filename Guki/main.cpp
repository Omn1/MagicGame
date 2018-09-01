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
	sf::View mainView(mainWindow.getDefaultView());

	sf::Clock clock;

	world.worldRect = sf::FloatRect(0, 0, 800, 600);

	while (mainWindow.isOpen())
	{
		// Track time
		float interactTime = (float)clock.getElapsedTime().asMicroseconds()/1000.0f;
		//std::cout << interactTime << std::endl;
		clock.restart();

		// Handle events
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mainWindow.close();
			else if(event.type == sf::Event::Resized)
				mainWindow.setView(mainView = sf::View(sf::FloatRect(0.f, 0.f,
					static_cast<float>(mainWindow.getSize().x),
					static_cast<float>(mainWindow.getSize().y))));
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Right) {
					world.player->handleSpellCast((sf::Vector2f)sf::Mouse::getPosition(mainWindow));
			}
		}
		world.player->handleInput((sf::Vector2f)sf::Mouse::getPosition(mainWindow));
		
		// Iterate
		//world.player->move(interactTime);
		world.updateObjects(interactTime);
		// Draw
		mainWindow.clear(sf::Color(255, 255, 255));
		world.draw(mainWindow,interactTime);
		mainWindow.display();
	}

	return 0;
}