#pragma once
#include "DynamicObject.h"
#include "Player.h"

class DynamicSpell : public DynamicObject {
public:
	DynamicSpell() {
		damage = 228;
		defaultSpeed = 2;
		isProjectile = 1;
		isPiercing = 0;
	}
	virtual void interactWithPlayer(Player * player, float interactTime) = 0;
	float damage;
	bool isPiercing;
};

class ArcaneBolt : public DynamicSpell {
public:
	ArcaneBolt(sf::Vector2f direction) {
		defaultSpeed = 0.2;
		damage = 5;
		dx = direction.x;
		dy = direction.y;
		animationLength = 1;
	}
	void interactWithPlayer(Player *player, float interactTime) {
		player->takeDamage(damage);
	}
	void AssignTexture(sf::Vector2f tTextureSize)
	{
		setTextureSize(tTextureSize);
		collisionBox = sf::FloatRect(sf::Vector2f(0,0),getTextureSize());
	}
	std::string getSpriteName(float interactTime) { return "ArcaneBolt"; }
};