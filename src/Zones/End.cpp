#include "Zones/End.h"

End::End()
{
	//Sets the rectangular data to it's default values.
	setPosition(0 , 0);
	setSize(sf::Vector2f(800 , 105));

	//Sets up the collision rectangle.
	sf::FloatRect BoundingBox = getGlobalBounds();
}