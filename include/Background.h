#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class Background : sf::RectangleShape
{
	private:
		sf::Texture BGTexture;

	public:
		sf::Sprite BGSprite;
		Background();
		Background(int iWidth,  int iHeight, std::string sTextureLocation);
};