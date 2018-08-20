#pragma once
#include <SFML/Graphics.hpp>
class Object {
public:
	Object() {
		textureScale = 1;
	};

	virtual ~Object() = default;

	sf::Vector2f position;
	virtual std::string getSpriteName(float interactTime) = 0;

	float textureScale;
	sf::Vector2f getTextureSize() {
		return textureSize * textureScale;
	}

	sf::FloatRect collisionBox;
	sf::FloatRect getCollisionBox()
	{
		sf::FloatRect tCollisionBox = collisionBox;
		tCollisionBox.left += position.x;
		tCollisionBox.top += position.y;
		return tCollisionBox;
	}

	virtual float getDrawOrderCriteria()
	{
		return position.y + textureSize.y * textureScale;
	}
	sf::FloatRect getRectangle() { return sf::FloatRect(position, getTextureSize()); }
protected:
	void setTextureSize(sf::Vector2f tTextureSize) { textureSize = tTextureSize; }
private:
	sf::Vector2f textureSize;
};

