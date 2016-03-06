#include "TextBox.h"

TextBox::TextBox()
{
	//Sets up the default text settings.
	if(!font.loadFromFile("Assets/Fonts/arial.ttf"))
	{
		std::cout<< "Error: Font \"arial\" was unable to load.";
	};

	Default_Text.setFont(font);
	Default_Text.setColor(sf::Color::White);
	Default_Text.setCharacterSize(20);
}

void TextBox::setTextCount(int iSize)
{
	//Loops to add all of the text to the vector.
	if (TextHolder.size() != iSize && iSize >= 0)
	{
		//Adds the default text to the holder as many times as required. 
		while(TextHolder.size() != iSize)
		{
			TextHolder.push_back(Default_Text);
		}
	}	
}

void TextBox::setBackground(sf::Color BGColour, int iPadding)
{
	//Initialises the sizing variables for the text.
	int iSizeX = 0;
	int iSizeY = 0;

	//For every item of text.
	for(int i = 0; i < TextHolder.size(); i++)
	{
		//Find the  widest piece of text and set the background box to the right width
		if( TextHolder[i].getLocalBounds().width > iSizeX)
		{
			iSizeX = TextHolder[i].getLocalBounds().width;
		}
	}

	//Set the Height of the background box to the size of all of the space put together.
	iSizeY = TextHolder[TextHolder.size()-1].getGlobalBounds().top + TextHolder[TextHolder.size()-1].getGlobalBounds().height - TextHolder[0].getGlobalBounds().top;
	

	//Sets the position and size of the box to fit behind the text with a small amount of padding and fills it in.
	setPosition(TextHolder[0].getPosition().x - (iSizeX / 2) - (iPadding / 2), TextHolder[0].getGlobalBounds().top - (iPadding / 2));
	setSize(sf::Vector2f(iSizeX + iPadding, iSizeY + iPadding ));
	setFillColor(BGColour);
}