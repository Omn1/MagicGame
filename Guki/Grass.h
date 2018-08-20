#pragma once
#include "DynamicObject.h"
class Grass : public DynamicObject {
public:
	Grass()
	{
		isBackground = true;
	}
	void AssignTexture(sf::Vector2f textureSize)
	{
		setTextureSize(textureSize);
	}
	std::string getSpriteName(float interactTime)
	{
		return "grass";
	}
};

