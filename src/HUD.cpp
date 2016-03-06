#include "HUD.h"

HUD::HUD()
{
	//Sets the HUD rectangular settings to their default settings.
	setPosition(0 , 0);
	setSize(sf::Vector2f(800 , 30));
	setFillColor(sf::Color(50,150,50,255));
}

void HUD::Draw(int Lives, int Score, int Level, int HighScore)
{
	//Adds 5 default text files to the text vector.
	setTextCount(5);
	
	//for every item of text in the holder.
	for(int i = 0; i < TextHolder.size(); i++)
	{
		//Sets the settings for the Lives
		if (i == 0)
		{
			TextHolder[i].setPosition(20 , getPosition().y);
			TextHolder[i].setString("Lives: " + std::to_string(Lives));
		}

		//Sets the settings for the Score
		else if (i == 1)
		{
			TextHolder[i].setPosition(200 , getPosition().y);
			TextHolder[i].setString("Score: " + std::to_string(Score));
		}

		//Sets the settings for the Title
		else if (i == 2)
		{
			TextHolder[i].setPosition(470, getPosition().y);
			TextHolder[i].setString("Level: " + std::to_string(Level));
		}

		//Sets the settings for the Title
		else if (i == 3)
		{
			TextHolder[i].setPosition(360 , getPosition().y);
			TextHolder[i].setString("Frogger");
		}

		//Sets the settings for the Highscore
		else if (i == 4)
		{
			TextHolder[i].setPosition(600 , getPosition().y);
			TextHolder[i].setString("HighScore: " + std::to_string(HighScore));
		}
	}
}