#include <iostream>
#include <iomanip>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Frog.h"
#include "Obstacles/Vehicle.h"
#include "Zones/Road.h"
#include "Zones/End.h"
#include "Background.h"
#include "HUD.h"

void SaveScore(int iScore); 
void LoadScore(int& iScore);
void StartScreen();
void InGame(int &iHighScore);
void EndScreen(int Score, int &HighScore);
void SetUpText(std::vector<sf::Text> &TextHolder,int iSize, sf::Font &Font);

sf::RenderWindow window(sf::VideoMode(800, 600), "Frogger");

int main()
{
	//Initialises the highscore.
	int iHighScore = 0;
	LoadScore(iHighScore);

	//Initialises the randomiser.
	srand(time(NULL));

	while (window.isOpen())
	{
		StartScreen();
		InGame(iHighScore);
	}
}

void SaveScore(int iScore) 
{
	//Saves a score value to a text file
	std::ofstream File1;
	File1.open("Assets/Text/Scores.txt", std::ios::out);
	File1 << iScore << "\n";
	File1.close();
}

void LoadScore(int &iScore)
{
	//Loads a score value to a text file
	std::ifstream File1;
	std::string sLineFromFile; 
	File1.open("Assets/Text/Scores.txt"); 

	if (File1.is_open())
	{
		getline(File1, sLineFromFile); 
		iScore = stoi(sLineFromFile);
	}
		
	else 
	{
		std::cout<<"Could not open file."; 
	}
	File1.close(); 
}

void StartScreen()
{
	//Initialises the background.
	Background BG1(window.getSize().x,  window.getSize().y, "Assets/Textures/Grass.png");

	//Initialises the text and adds 2 default text files to the textbox.
	TextBox TextBox1;
	TextBox1.setTextCount(2);

	TextBox1.setPosition(150, 100);
	TextBox1.setSize(sf::Vector2f(500, 300));

	//for every item of text in the holder.
	for(int i = 0; i < TextBox1.TextHolder.size(); i++)
	{
		//Sets the settings for the Title
		if (i == 0)
		{
			TextBox1.TextHolder[i].setCharacterSize(100);
			TextBox1.TextHolder[i].setString("Frogger");
			TextBox1.TextHolder[i].setPosition(window.getSize().x / 2 , (window.getSize().y / 2) - 100);
		}

		//Sets the settings for the Entry prompt
		if (i == 1)
		{
			TextBox1.TextHolder[i].setCharacterSize(40);
			TextBox1.TextHolder[i].setString("Press Enter to start");
			TextBox1.TextHolder[i].setPosition(window.getSize().x / 2 , (window.getSize().y / 2));
		}

		//Sets all of the text to black
		TextBox1.TextHolder[i].setColor(sf::Color::Black);

		//Positions the text in the centre of the screen
		TextBox1.Box = TextBox1.TextHolder[i].getLocalBounds();
		TextBox1.TextHolder[i].setOrigin(TextBox1.Box.width / 2, TextBox1.Box.height);
	}

	TextBox1.setBackground(sf::Color(50,150,50,255), 50);

	while(window.isOpen())
	{
		//Input Entry
		sf::Event event;
		while (window.pollEvent(event))
		{
			//If the X in the top corner is pressed the game closes.
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}

			//If the player presses enter the game starts
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code==sf::Keyboard::Return)
				{
					return;
				}
			}
		}
		//Adds a green background.
		window.clear(sf::Color::Green);

		//Draw the Background
		window.draw(BG1.BGSprite);
		window.draw(TextBox1);
		for(int i = 0; i < TextBox1.TextHolder.size(); i++)
		{
			//Draws the text to the screen
			window.draw(TextBox1.TextHolder[i]);
		}
		//Refreshes the display
		window.display();
	}
}

void InGame(int &iHighScore)
{
	//Declares the timer.
	sf::Clock Timer;

	//Initialises the background.
	Background BG1(window.getSize().x,  window.getSize().y, "Assets/Textures/Grass.png");

	//Initialises the player.
	Frog Player;

	//Initialises the roads.
	Road Road1;
	Road Road2;

	//Initialises the end zone.
	End End1;

	//Initialises the HUD.
	HUD HUD1;

	//Sets the positions and sizes of the roads.
	//Road 1
	Road1.SetY(125);
	Road1.setLanes(7);

	//Road 2
	Road2.SetY(350);
	Road2.setLanes(7);

	//Game Loop
	while (window.isOpen())
	{
		//Draws the green background to the screen
		window.clear(sf::Color::Green);

		//Input Entry
		sf::Event event;
		while (window.pollEvent(event))
		{
			//If the X in the top right of the screen is pressed the game closes.
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				//If up or w is pressed the player moves up.
				if (event.key.code==sf::Keyboard::Up || event.key.code==sf::Keyboard::W)
				{
					Player.ToggleDirection(0, true);
				}

				//If down or d is pressed the player moves down.
				if (event.key.code==sf::Keyboard::Down || event.key.code==sf::Keyboard::S)
				{
					Player.ToggleDirection(1, true);
				}
				
				//If left or a is pressed the player moves left.
				if (event.key.code==sf::Keyboard::Left || event.key.code==sf::Keyboard::A)
				{
					Player.ToggleDirection(2, true);
				}

				//If right or d is pressed the player moves right.
				if (event.key.code==sf::Keyboard::Right || event.key.code==sf::Keyboard::D)
				{
					Player.ToggleDirection(3, true);
				}
			}
		}

		//Every 60th of a second the...
		if(Timer.getElapsedTime().asSeconds() > 1.0 / 60.0)
		{
			//Player is moved
			Player.Move(window.getSize().x, window.getSize().y);

			//Every Car on Road 1 is moved.
			for (int i = 0; i< Road1.getLanes(); i++)
			{
				Road1.VehicleList[i].Move(window.getSize().x, window.getSize().y);
			}

			//Every Car on Road 2 is moved.
			for (int i = 0; i< Road2.getLanes(); i++)
			{
				Road2.VehicleList[i].Move(window.getSize().x, window.getSize().y);
			}

			//The timer is reset.
			Timer.restart();
		}
		
		//For every car on road 1 collision with the player is checked.
		for (int i = 0; i< Road1.getLanes(); i++)
		{
			Player.Collision(Road1.VehicleList[i], iHighScore);
		}

		//For every car on road 2 collision with the player is checked.
		for (int i = 0; i< Road2.getLanes(); i++)
		{
			Player.Collision(Road2.VehicleList[i], iHighScore);
		}

		//Collision between the player and the end is checked.
		if(Player.Collision(End1))
		{
			//Roads are randomised again.
			Road1.setLanes(0);
			Road1.setLanes(7);
			Road2.setLanes(0);
			Road2.setLanes(7);
		};
		
		//Draw the Background
		window.draw(BG1.BGSprite);

		//The Roads are drawn
		window.draw(Road1);
		window.draw(Road2);

		//The player is drawn
		window.draw(Player.CurrentSprite);

		//Every car on road 1 is drawn
		for (int i = 0; i< Road1.getLanes(); i++)
		{
			window.draw(Road1.VehicleList[i].CurrentSprite);
		}

		//Every car on road 2 is drawn
		for (int i = 0; i< Road2.getLanes(); i++)
		{
			window.draw(Road2.VehicleList[i].CurrentSprite);
		}

		//The HUD box is drawn
		window.draw(HUD1);

		//The text on the HUD is drawn.
		HUD1.Draw(Player.getLives(),Player.getScore(), Player.getLevel(), iHighScore);
		for (int i = 0; i < HUD1.TextHolder.size(); i++)
		{
			window.draw(HUD1.TextHolder[i]);
		}

		//The window is refreshed.
		window.display();

		//If the player runs out of lives the end screen is shown and then the game returns to the menu.
		if (Player.getLives() <= 0)
		{
			EndScreen(Player.getScore(), iHighScore);
			SaveScore(iHighScore);
			return;
		}
	}
}

void EndScreen(int Score, int& HighScore)
{
	//Initialises the background.
	Background BG1(window.getSize().x,  window.getSize().y, "Assets/Textures/Grass.png");

	//Initialises the text and adds 3 default text files to the textbox.
	TextBox TextBox1;
	TextBox1.setTextCount(4);

	//for every item of text in the holder.
	for(int i = 0; i < TextBox1.TextHolder.size(); i++)
	{
		//Sets the settings for the Title
		if (i == 0)
		{
			TextBox1.TextHolder[i].setCharacterSize(100);
			TextBox1.TextHolder[i].setString("Game Over");
			TextBox1.TextHolder[i].setPosition(window.getSize().x / 2 , (window.getSize().y / 2) - 100);
		}

		//Sets the settings for the Score display
		if (i == 1)
		{
			TextBox1.TextHolder[i].setCharacterSize(40);
			TextBox1.TextHolder[i].setString("Score: " + std::to_string(Score));
			TextBox1.TextHolder[i].setPosition(window.getSize().x / 2 , (window.getSize().y / 2));
		}

		//Sets the settings for the HighScore display
		if (i == 2)
		{
			TextBox1.TextHolder[i].setCharacterSize(40);
			TextBox1.TextHolder[i].setString("HighScore: " + std::to_string(HighScore));
			TextBox1.TextHolder[i].setPosition(window.getSize().x / 2 , TextBox1.TextHolder[i - 1].getPosition().y + 40);
		}

		//Sets the settings for the entry prompt
		if (i == 3)
		{
			TextBox1.TextHolder[i].setCharacterSize(40);
			TextBox1.TextHolder[i].setString("Press enter to go back to the menu.");
			TextBox1.TextHolder[i].setPosition(window.getSize().x / 2 , TextBox1.TextHolder[i - 1].getPosition().y + 80);
		}

		//Sets all of the text to black
		TextBox1.TextHolder[i].setColor(sf::Color::Black);

		//Positions the text in the centre of the screen
		TextBox1.Box = TextBox1.TextHolder[i].getLocalBounds();
		TextBox1.TextHolder[i].setOrigin(TextBox1.Box.width / 2, TextBox1.Box.height);
	}

	TextBox1.setBackground(sf::Color(50,150,50,255), 50);

	while(window.isOpen())
	{
		//Input Entry
		sf::Event event;
		while (window.pollEvent(event))
		{
			//If the X in the top corner is pressed the game closes.
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				//If the player presses enter the main menu will appear.
				if (event.key.code==sf::Keyboard::Return)
				{
					return;
				}
			}
		}
		//Adds a green background.
		window.clear(sf::Color::Green);

		//Draw the Background
		window.draw(BG1.BGSprite);

		//Draws the textbox background to the screen.
		window.draw(TextBox1);
		for(int i = 0; i < TextBox1.TextHolder.size(); i++)
		{
			//Draws the text to the screen
			window.draw(TextBox1.TextHolder[i]);
		}

		//Refreshes the display
		window.display();
	}
}