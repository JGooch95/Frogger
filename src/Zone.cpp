#include "Zone.h"

Zone::Zone()
{
	//Sets the rectangular data to its default settings.
	setPosition(0 , 0);
	setSize(sf::Vector2f(800 , 200));
	setFillColor(sf::Color::White);	
	sf::FloatRect BoundingBox = getGlobalBounds();
}

void Zone::SetY(int iValue)
{
	//Sets the y coordinate to the value given.
	setPosition(getPosition().x , iValue);
}