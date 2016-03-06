#include "Obstacles/Vehicle.h"

Vehicle::Vehicle(){
	//Sets the default position and size.
	setPosition(-getPosition().x , 320);
	setSize(sf::Vector2f(25 , 50));
}

Vehicle::Vehicle(int iWidth, int iHeight, std::string sTextureLoc)
{
	//Sets the position, size and texture for the vehicle.
	setPosition(-getPosition().x , 320);
	setSize(sf::Vector2f(iWidth , iHeight));
	if(!CurrentTexture.loadFromFile(sTextureLoc))
	{
		std::cout << sTextureLoc + " Texture failed to loaded \n";
	}
}