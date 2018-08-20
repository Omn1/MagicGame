#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Object.h"

void normalize(float &x, float &y);

bool cmpImgDraw(Object* firstItem, Object* secondItem);

sf::Vector2f get_deltas(std::string direction);

sf::Vector2f getCastOffset(std::string direction);

sf::Vector2f transpose(sf::Vector2f a);