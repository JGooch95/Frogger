#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Zone : public sf::RectangleShape
{
	public:
		sf::FloatRect BoundingBox;
		Zone();
		void SetY(int iValue);
};