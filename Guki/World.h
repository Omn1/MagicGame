#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Object.h"
#include "Grass.h"
#include "GridList.h"

class World;

#include "Player.h"
#include "Spells.h"


class World {
public:
	World();

	bool init();

	bool initSpriteMap();

	void draw(sf::RenderTarget &target, float drawTime);

	void updateObjects(float interactTime);

	void interact(float interactTime);

	void generate(int xSize, int ySize);

	void initPlayer();

	void initGrass(sf::Vector2f position);

	void initDynamicSpell(DynamicSpell * spell, sf::Vector2f start, sf::Vector2f finish);

	void initArcaneBolt(sf::Vector2f start, sf::Vector2f finish);

	void initFireBall(sf::Vector2f start, sf::Vector2f finish);

	/*void initHouse(sf::Vector2f position)
	{
		House *house = new House();
		house->position = position;
		house->setTextureSize((sf::Vector2f)(spriteMap[house->getSpriteName(0)]->getSize()));
		staticGrid.addObject(house);
	}*/

	GridList<DynamicObject> dynamicGrid;
	GridList<Object> staticGrid;
	GridList<DynamicSpell> projectiles;
	std::map<std::string, sf::Texture*> spriteMap;
	Player *player;
	float textureScale;

	sf::FloatRect worldRect;
};

