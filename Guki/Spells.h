#pragma once
#include "DynamicObject.h"
#include "Player.h"

class DynamicSpell : public DynamicObject {
public:
	DynamicSpell() {
		damage = 228;
		defaultSpeed = 2;
		isPiercing = 0;
		hasLifeTime = 0;
		lifeTime = 0;
		spellName = "spell";
	}
	virtual void interactWithPlayer(Player * player, float interactTime) = 0;
	virtual void updateState(float interactTime) {
		move(interactTime);
		if (hasLifeTime) {
			lifeTime -= interactTime;
		}
	}
	void setDirection(sf::Vector2f direction) {
		dx = direction.x;
		dy = direction.y;
	}
	virtual std::string getSpriteName(float interactTime) {
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
		return spellName + std::to_string(currentSpriteNum);
	}
	virtual void AssignTexture(sf::Vector2f tTextureSize) = 0;
	float damage;
	float lifeTime;
	bool isPiercing;
	bool hasLifeTime;
	std::string spellName;
};

class ArcaneBolt : public DynamicSpell {
public:
	ArcaneBolt(sf::Vector2f direction) {
		defaultSpeed = 2;
		damage = 5;
		dx = direction.x;
		dy = direction.y;
		animationLength = 1;
		spellName = "ArcaneBolt";
	}
	void interactWithPlayer(Player *player, float interactTime) {
		player->takeDamage(damage);
	}
	void AssignTexture(sf::Vector2f tTextureSize)
	{
		setTextureSize(tTextureSize);
		collisionBox = sf::FloatRect(sf::Vector2f(0,0),getTextureSize());
	}
};

class FireBall : public DynamicSpell {
public:
	FireBall(sf::Vector2f direction) {
		defaultSpeed = 0.3;
		damage = 0.01;
		dx = direction.x;
		dy = direction.y;
		animationLength = 3;
		spellName = "FireBall";
	}
	void interactWithPlayer(Player *player, float interactTime) {
		player->takeDamage(damage);
		player->setHpPerTickBuff(0.005, 5000);
	}
	void AssignTexture(sf::Vector2f tTextureSize)
	{
		setTextureSize(tTextureSize);
		collisionBox = sf::FloatRect(sf::Vector2f(0, 0), getTextureSize());
	}
};