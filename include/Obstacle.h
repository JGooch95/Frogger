#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Obstacle : public sf::RectangleShape
{
	protected:
		int iDirection;
		int iMaxMoveSpeed;
		int iMinMoveSpeed;
		int iMoveSpeed;
		sf::Texture CurrentTexture;
	
	public:
		sf::Sprite CurrentSprite;
		sf::FloatRect BoundingBox;
		Obstacle();
		void setDirection(int iValue);
		void setMoveSpeed(int iValue);
		void Move(int iWindowWidth, int iWindowHeight);
		void setX(int iValue);
		void setY(int iValue);
};