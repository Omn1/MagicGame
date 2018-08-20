#include "Player.h"
#include "World.h"

Player::Player()
{
	defaultSpeed = 0.5;
	animationLength = 3;

	hp = maxHp = 200;
	resetBuffs();
}

inline std::string Player::getSpriteName(float interactTime)
{
	std::string res;
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
	if (!isMoving)currentSpriteNum = 0;
	if (direction == "LEFT")
	{
		res = "heroMoveLeft";
	}
	if (direction == "RIGHT")
	{
		res = "heroMoveRight";
	}
	if (direction == "UP")
	{
		res = "heroMoveUp";
	}
	if (direction == "DOWN")
	{
		res = "heroMoveDown";
	}
	if (direction == "UPLEFT")
	{
		res = "heroMoveLeft";
	}
	if (direction == "UPRIGHT")
	{
		res = "heroMoveRight";
	}
	if (direction == "DOWNLEFT")
	{
		res = "heroMoveLeft";
	}
	if (direction == "DOWNRIGHT")
	{
		res = "heroMoveRight";
	}
	res += std::to_string(currentSpriteNum);
	return res;
}

void Player::AssignTexture(sf::Vector2f textureSize)
{
	setTextureSize(textureSize);
	collisionBox = sf::FloatRect(sf::Vector2f(0, 0), getTextureSize());
}

sf::Vector2f Player::getSpellStartPoint()
{
	//return position + transpose(getTextureSize())*0.5f + sf::Vector2f(getTextureSize().y*get_deltas(direction).x, getTextureSize().x*get_deltas(direction).y);
	sf::Vector2f startPoint = position + sf::Vector2f(collisionBox.left, collisionBox.top);
	if (direction == "DOWN") {
		startPoint += sf::Vector2f(0, collisionBox.height);
		startPoint.x += collisionBox.width*0.5f;
	}
	else if (direction == "UP") {
		startPoint.x += collisionBox.width*0.5f;
	}
	else if (direction == "LEFT") {
		startPoint.y += collisionBox.height*0.5f;
	}
	else if (direction == "RIGHT") {
		startPoint += sf::Vector2f(collisionBox.width, 0);
		startPoint.y += collisionBox.height*0.5f;
	}
	return startPoint;
}

void Player::handleSpellCast(sf::Vector2f mousePos)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		setSpeedBuff(1.5, 10000);
	}
	else world->initArcaneBolt(getSpellStartPoint(), mousePos, getCastOffset(direction), (direction=="LEFT" || direction=="RIGHT"));
}

void Player::handleInput()
{
	isMoving = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction = "LEFT";
	}
	else
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			direction = "RIGHT";
		}
		else
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				direction = "UP";
			}
			else
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					direction = "DOWN";
				}
				else isMoving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		dy = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		dy = 1;
	}
	else {
		dy = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		dx = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		dx = 1;
	}
	else {
		dx = 0;
	}
}

float Player::getHp()
{
	return hp;
}

void Player::setHp(float thp)
{
	hp = thp;
}

void Player::takeDamage(float dmg)
{
	hp = std::min(maxHp, std::max(0.0f, hp - dmg * armorMultiplier));
}

void Player::updateState(float interactTime)
{
	move(std::min(interactTime, speedMultiplierTime));
	if (speedMultiplierTime - interactTime < 0) {
		speedMultiplier = 1;
		move(interactTime - speedMultiplierTime);
	}
	speedMultiplierTime = std::max(0.0f, speedMultiplierTime - interactTime);

	armorMultiplierTime = std::max(0.0f, speedMultiplierTime - interactTime);

	if (interactTime - hpPerTickTime > 0) {
		takeDamage(hpPerTick * hpPerTickTime);
		hpPerTick = 0;
		hpPerTickTime = 0;
	}
	else {
		hpPerTick -= interactTime;
	}
}

void Player::resetBuffs()
{
	speedMultiplier = 1;
	speedMultiplierTime = 0;
	armorMultiplier = 1;
	armorMultiplierTime = 0;
	hpPerTick = 0;
	hpPerTickTime = 0;
}

void Player::setSpeedBuff(float buff, float buffTime) {
	speedMultiplier = buff;
	speedMultiplierTime = buffTime;
}

void Player::setArmorBuff(float buff, float buffTime) {
	armorMultiplier = buff;
	armorMultiplierTime = buffTime;
}

void Player::setHpPerTickBuff(float buff, float buffTime) {
	hpPerTick = buff;
	hpPerTickTime = buffTime;
}

float Player::getSpeed()
{
	return defaultSpeed * speedMultiplier;
}
