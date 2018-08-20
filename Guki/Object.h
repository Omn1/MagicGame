#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionArea.h"
class Object {
public:
	Object() {
		textureScale = 1;
		rotation = 0;
	};

	virtual ~Object() = default;

	sf::Vector2f position;
	virtual std::string getSpriteName(float interactTime) = 0;

	float textureScale;
	sf::Vector2f tgetTextureSize() {
		return textureSize * textureScale;
	}

	CollisionArea collisionArea;

	virtual float getDrawOrderCriteria()
	{
		return position.y + textureSize.y * textureScale;
	}
	 
	float rotation;

	sf::FloatRect getRectangle() { return sf::FloatRect(position, tgetTextureSize()); }
protected:
	void setTextureSize(sf::Vector2f tTextureSize) { textureSize = tTextureSize; }
private:
	sf::Vector2f textureSize;
};

