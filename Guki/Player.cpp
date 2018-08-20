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
	collisionArea = CollisionArea(sf::FloatRect(position, tgetTextureSize()), sf::Vector2f(1,0));
}

sf::Vector2f Player::getSpellStartPoint()
{
	//return position + transpose(getTextureSize())*0.5f + sf::Vector2f(getTextureSize().y*get_deltas(direction).x, getTextureSize().x*get_deltas(direction).y);
	return position + tgetTextureSize()*0.5f;
}

void Player::handleSpellCast(sf::Vector2f mousePos)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		setSpeedBuff(1.5, 10000);
	}
	else world->initFireBall(getSpellStartPoint(), mousePos);
}

void Player::handleInput(sf::Vector2f mousePos)
{
	if (isCCW(position + sf::Vector2f(0, tgetTextureSize().y), position + sf::Vector2f(tgetTextureSize().x, 0), mousePos)) {
		if (isCCW(position, position + tgetTextureSize(), mousePos)) {
			direction = "UP";
		}
		else {
			direction = "LEFT";
		}
	}
	else {
		if (isCCW(position, position + tgetTextureSize(), mousePos)) {
			direction = "RIGHT";
		}
		else {
			direction = "DOWN";
		}
	}
	isMoving = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	if (!isMoving) {
		dx = dy = 0;
	}
	else {
		sf::Vector2f moveDirection = mousePos - (position + 0.5f*tgetTextureSize());
		dx = moveDirection.x;
		dy = moveDirection.y;
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
	//hp = std::min(maxHp, std::max(0.0f, hp - dmg * armorMultiplier));
	hp -= dmg;
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
		hpPerTickTime -= interactTime;
		takeDamage(hpPerTick * interactTime);
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
