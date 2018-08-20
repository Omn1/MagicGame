#pragma once
#include "Object.h"
#include "Misc.h"
#include <iostream>

class DynamicObject : public Object {
public:
	DynamicObject() {
		direction = "DOWN";
		timeForNewSprite = 100;
		currentSpriteNum = 1;
		isMoving = 0;
	}
	float defaultSpeed;
	virtual float getSpeed() { return defaultSpeed; }
	float dx, dy;
	bool isMoving;
	virtual void updateState(float interactTime) {
		move(interactTime);
	}
protected:
	std::string direction;
	std::string currentSpriteName;
	int currentSpriteNum, animationLength;
	float timeForNewSprite, animationTime;
	void move(float interactTime)
	{
		normalize(dx, dy);
		sf::Vector2f deltaPos(dx * getSpeed() * interactTime, dy * getSpeed() * interactTime);
		//std::cout << deltaPos.x << " " << deltaPos.y << std::endl;
		position += deltaPos;
	}
};

