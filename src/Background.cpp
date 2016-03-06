#include "Background.h"

Background::Background()
{
	//Loads the default texture
	if(!BGTexture.loadFromFile("Assets/Textures/Grass.png"))
	{
		std::cout << "Grass Texture not loaded";
	}

	BGTexture.setRepeated(true); //Sets the texture to repeat for the wallpaper.

	//Sets the default texture and positions it.
	BGSprite.setTexture(BGTexture);
	BGSprite.setTextureRect(sf::IntRect(0,0, 800,  600));
	BGSprite.setPosition(0,0);
}

Background::Background(int iWidth,  int iHeight, std::string sTextureLocation)
{
	//Loads the texture given
	if(!BGTexture.loadFromFile(sTextureLocation))
	{
		std::cout << "Background Texture not loaded";
	}

	BGTexture.setRepeated(true); //Sets the texture to repeat for the wallpaper.

	//Sets the texture and positions it.
	BGSprite.setTexture(BGTexture);
	BGSprite.setTextureRect(sf::IntRect(0,0, iWidth, iHeight));
	BGSprite.setPosition(0,0);
}