#include "Obstacle.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Obstacle::Obstacle()
{
	//Sets the default Movement variables
	iMaxMoveSpeed = 5;
	iMinMoveSpeed = 3;
	iMoveSpeed = 4;

	//Sets up the collision box for the obstacle.
	sf::FloatRect BoundingBox = getGlobalBounds();

	//Sets up the default direction
	iDirection = 3;

	//Applying the values to the rectangular space
	setPosition(200 , 50);
	setSize(sf::Vector2f(25 , 25));
	setFillColor(sf::Color::Red);

	if (!iMinMoveSpeed > 0)
	{
		iMinMoveSpeed = 1;
	}
};

void Obstacle::Move(int iWindowWidth, int iWindowHeight)
{
	//Declares variable which stores random number.
	int iRandom;
	switch(iDirection)
	{
		//If the direction is left
		case 3:
			setPosition(getPosition().x - iMoveSpeed , getPosition().y); //The obstacle moves left by the movement speed.
			CurrentSprite.setRotation(0.0f); //Rotates the obstacle sprite to the left.
			break;

		//If the direction is right
		case 4:
			setPosition(getPosition().x + iMoveSpeed , getPosition().y); //The obstacle moves right by the movement speed.
			CurrentSprite.setRotation(180.0f); //Rotates the obstacle sprite to the right.
			break;
	}

	//If the obstacle leaves the window's right side it will come out of it's left side
	if (getPosition().x > iWindowWidth + getSize().x)
	{
		setPosition(-getSize().x , getPosition().y);
		iRandom = (rand() % iMaxMoveSpeed) + iMinMoveSpeed;
		setMoveSpeed(iRandom);
	}

	//If the obstacle leaves the window's left side it will come out of it's right side
	if (getPosition().x <  -getSize().x)
	{
		setPosition(iWindowWidth + getSize().x , getPosition().y);
		iRandom = (rand() % iMaxMoveSpeed) + iMinMoveSpeed;
		setMoveSpeed(iRandom);
	}

	//Sets up the texture for drawing.
	CurrentSprite.setTexture(CurrentTexture);
	CurrentSprite.setScale(getSize().x / CurrentTexture.getSize().x, getSize().y / CurrentTexture.getSize().y);
	CurrentSprite.setOrigin((CurrentSprite.getGlobalBounds().width / 2) / CurrentSprite.getScale().x, (CurrentSprite.getGlobalBounds().height / 2) / CurrentSprite.getScale().y);
	CurrentSprite.setPosition(getPosition().x + (getSize().x / 2) , getPosition().y  + (getSize().y / 2) );
};

void Obstacle::setDirection(int iValue)
{
	//Sets the direction to the value given.
	iDirection = iValue;
};

void Obstacle::setMoveSpeed(int iValue)
{
	//Sets the movespeed to the value given.
	iMoveSpeed = iValue;
};

void Obstacle::setX(int iValue)
{
	//Sets the X coordinate to the value given.
	setPosition(iValue , getPosition().y);
};

void Obstacle::setY(int iValue)
{
	//Sets the Y coordinate to the value given.
	setPosition(getPosition().x , iValue);
};