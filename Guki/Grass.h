#pragma once
#include "DynamicObject.h"
class Grass : public DynamicObject {
public:
	Grass() {}
	void AssignTexture(sf::Vector2f textureSize)
	{
		setTextureSize(textureSize);
	}
	std::string getSpriteName(float interactTime)
	{
		return "grass";
	}
	float getDrawOrderCriteria()
	{
		return -2000000000;
	}
};

