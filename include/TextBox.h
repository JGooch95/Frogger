#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class TextBox: public sf::RectangleShape
{
	protected:
		sf::Font font;
		sf::Text Default_Text;

	public:
		std::vector<sf::Text> TextHolder;
		sf::FloatRect Box;
		TextBox();
		void setTextCount(int iSize);
		void setBackground(sf::Color BGColour, int iPadding);

};