#pragma once
#include "DynamicObject.h"
#include "Player.h"
#include "Misc.h"

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
		collisionArea.dx = dx = direction.x;
		collisionArea.dy = dy = direction.y;
	}
	virtual sf::Vector2f getCenter() { return tgetTextureSize()*0.5f; }
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
		rotation = getAngle(sf::Vector2f(dx, dy));
		std::cout << rotation << std::endl;
		collisionArea = CollisionArea(sf::FloatRect(position, tgetTextureSize()), get_deltas(direction));
	}
};

class FireBall : public DynamicSpell {
public:
	FireBall(sf::Vector2f direction) {
		defaultSpeed = 0.8;
		damage = 15;
		dx = direction.x;
		dy = direction.y;
		animationLength = 3;
		isPiercing = 1;
		spellName = "FireBall";
	}
	void interactWithPlayer(Player *player, float interactTime) {
		player->takeDamage(damage);
		player->setHpPerTickBuff(0.005, 5000);
	}
	void AssignTexture(sf::Vector2f tTextureSize)
	{
		setTextureSize(tTextureSize);
		rotation = getAngle(sf::Vector2f(dx, dy));
		std::cout << rotation << std::endl;
		collisionArea = CollisionArea(sf::FloatRect(position, tgetTextureSize()), sf::Vector2f(dx,dy));
	}
};