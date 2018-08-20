#pragma once
#include "DynamicObject.h"

class Player;
class World;

class Player : public DynamicObject {
public:
	Player();
	std::string getSpriteName(float interactTime);
	void AssignTexture(sf::Vector2f textureSize);
	sf::Vector2f getSpellStartPoint();
	World *world;
	void handleSpellCast(sf::Vector2f mousePos);
	void handleInput(sf::Vector2f mousePos);
	float getHp();
	void setHp(float thp);
	void takeDamage(float dmg);
	void updateState(float interactTime);
	void resetBuffs();
	void setSpeedBuff(float buff, float buffTime);
	void setArmorBuff(float buff, float buffTime);
	void setHpPerTickBuff(float buff, float buffTime);
	float getSpeed();
protected:	
	float hp, maxHp;
	float speedMultiplier, speedMultiplierTime;
	float armorMultiplier, armorMultiplierTime;
	float hpPerTick, hpPerTickTime;
};

