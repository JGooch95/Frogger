#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Obstacles/Vehicle.h"
#include "Zones/End.h"
#include <vector>

class Frog : public sf::RectangleShape
{
	private:
		int iHopSpeed;
		int iHopDistance;

		sf::FloatRect BoundingBox;

		std::vector<int> iNextLocation;
		std::vector<bool> bDirection;
		sf::Texture CurrentTexture;

		int iLives;
		int iScore;
		int iLevel;

	public:
		sf::Sprite CurrentSprite;
		Frog();
		void Move(int iWindowWidth, int iWindowHeight);
		void StopMove();
		void ToggleDirection(int iDirection, bool bToggle);
		void Kill(int &iHighscore);
		void ResetPosition();
		void WindowCollision(int iWindowWidth, int iWindowHeight);
		bool Collision(Vehicle& Obj1, int &iHighscore);
		bool Collision(End& Obj1);
		int getLives();
		int getScore();
		int getLevel();
};