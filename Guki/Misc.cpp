#include "Misc.h"
#include "Object.h"

sf::RenderWindow mainWindow(sf::VideoMode(1280, 720), "SFML works!");

const float PI = 3.1415926535;
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
	return sf::Vector2f(0, 0);
}

sf::Vector2f transpose(sf::Vector2f a)
{
	return sf::Vector2f(a.y, a.x);
}

float orientedArea(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c)
{
	return ((b.x - a.x)*(b.y + a.y) + (c.x - b.x)*(c.y + b.y) + (a.x - c.x)*(a.y + c.y));
}

bool isCCW(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c)
{
	return orientedArea(a, b, c) >= 0;
}

inline bool segIntersect_1(float a, float b, float c, float d) {
	if (a > b)std::swap(a, b);
	if (c > d)std::swap(c, d);
	return std::max(a, c) <= std::min(b, d);
}
bool segIntersect(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d) {
	return segIntersect_1(a.x, b.x, c.x, d.x) && segIntersect_1(a.y, b.y, c.y, d.y) && orientedArea(a, b, c) * orientedArea(a, b, d) <= 0 && orientedArea(c, d, a) * orientedArea(c, d, b) <= 0;
}

float getAngle(sf::Vector2f direction) {
	return atan2(direction.y, direction.x) / PI * 180;
}

bool checkSignPressed(std::string sign)
{
	for (int i = 0; i < sign.size(); i++) {
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(sign[i] - 'a')))return 0;
	}
	return 1;
}