#include "Misc.h"
#include "Object.h"
void normalize(float &x, float &y) {
	if (x == 0 && y == 0)
		return;
	float h = sqrtf(x*x + y*y);
	x *= 1 / h;
	y *= 1 / h;
}

bool cmpImgDraw(Object* firstItem, Object* secondItem)
{
	return firstItem->getDrawOrderCriteria() < secondItem->getDrawOrderCriteria();
}

sf::Vector2f get_deltas(std::string direction) {
	if (direction == "UP")
		return sf::Vector2f(0, -1);
	else if (direction == "DOWN")
		return sf::Vector2f(0, 1);
	else if (direction == "LEFT")
		return sf::Vector2f(-1, 0);
	else if (direction == "RIGHT")
		return sf::Vector2f(1, 0);
}

sf::Vector2f getCastOffset(std::string direction) {
	if (direction == "UP")
		return sf::Vector2f(0, -1);
	else if (direction == "DOWN")
		return sf::Vector2f(0, 0);
	else if (direction == "LEFT")
		return sf::Vector2f(-1, 0);
	else if (direction == "RIGHT")
		return sf::Vector2f(0, 0);
}

sf::Vector2f transpose(sf::Vector2f a)
{
	return sf::Vector2f(a.y, a.x);
}
