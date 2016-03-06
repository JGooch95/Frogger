#include "Frog.h"

Frog::Frog()
{
	//Applying the values to the rectangular space
	ResetPosition();
	setSize(sf::Vector2f(25 , 25));
	setFillColor(sf::Color::Green);

	//Fills the Next Location variable with the starting x and y values
	iNextLocation.resize(2);
	iNextLocation[0] = getPosition().x;
	iNextLocation[1] = getPosition().y;

	//Sets the hop speed and distance to their default values.
	iHopSpeed = 5; // 5
	iHopDistance = 25;

	//Sets up the bounding box for collision.
	BoundingBox = getGlobalBounds();

	//Loads the frog texture
	if(!CurrentTexture.loadFromFile("Assets/Sprites/Frog_SpriteSheet.png"))
	{
		std::cout << "Frog Texture not loaded";
	}

	//Sets and Positions the texture for use.
	CurrentSprite.setTexture(CurrentTexture);
	CurrentSprite.setScale((getSize().x / CurrentTexture.getSize().x) * 2, getSize().y / CurrentTexture.getSize().y);
	CurrentSprite.setPosition(getPosition().x + (getSize().x /2), getPosition().y + (getSize().y /2));
	CurrentSprite.setOrigin(getSize().x / 2, getSize().y / 2);

	//Sets the texture to the first sprite
	CurrentSprite.setTextureRect(sf::IntRect(0,0,25,25));

	//Sets all Scoring variables to default
	iScore = 0;
	iLevel = 1;

	bDirection.resize(4);

	//Sets all of the direction values to false.
	for (int i = 0; i == bDirection.size() - 1 ; i++)
	{
		bDirection[i] = false;
	}

	//Sets the lives to the default value.
	iLives = 3;

	//Error Checks the Variables
	while( iHopSpeed > iHopDistance && iHopSpeed <= 0)
	{
		if (iHopSpeed > iHopDistance)
		{
			//Makes maximum hop speed equal to the hop distance.
			iHopSpeed = iHopDistance;
		}
		if (iHopSpeed <= 0)
		{
			//Makes maximum hop speed equal to minimum speed
			iHopSpeed *= -1;
		}
	}

	if (iHopDistance <= 0)
	{
		//Makes maximum hop speed equal to minimum speed
		iHopDistance *= -1;
	}
}

void Frog::Move(int iWindowWidth, int iWindowHeight)
{
	//For every direction.
	for(int i=0; i < bDirection.size(); i++)
	{
		//If the movement is true.
		if(bDirection[i] == true)
		{
			//If the movement is in the y direction.
			if (i == 0 || i == 1)
			{
				//If the position of the frog is equal to it's destination on the y axis.
				if (getPosition().y == iNextLocation[1])
				{
					switch(i)
					{
						//If the frog is going up.
						case 0:
							iNextLocation[1] -= iHopDistance; // The destination is incremented by the hop distance.
							break; 

						//If the frog is going down.
						case 1:
							iNextLocation[1] += iHopDistance; // The destination is incremented by the hop distance.
							break;
					}
				}

				//If the position of the frog is not equal to it's destination on the y axis.
				else
				{
					CurrentSprite.setTextureRect(sf::IntRect(25,0,25,25));
					switch(i)
					{
						//If the frog is going up.
						case 0:
							CurrentSprite.setRotation(0.0f); //Frog is faced upwards.
							setPosition(getPosition().x, getPosition().y - iHopSpeed); //Frog is moved up by the hop speed.
							break;

						//If the frog is going down.
						case 1:
							CurrentSprite.setRotation(180.0f); //Frog is faced downwards.
							setPosition(getPosition().x, getPosition().y + iHopSpeed); //Frog is moved down by the hop speed.
							break;
					}

					//If the frog reaches its destination it's movement in the direction is stopped.
					if (getPosition().y == iNextLocation[1])
					{
						ToggleDirection(i , false);
						CurrentSprite.setTextureRect(sf::IntRect(0,0,25,25));
					}
				}
			}

			//If the movement is in the x direction.
			else if (i == 2 || i == 3)
			{
				//If the position of the frog is equal to it's destination on the x axis.
				if (getPosition().x == iNextLocation[0])
				{
					switch(i)
					{
						//If the frog is going left.
						case 2:
							iNextLocation[0] -= iHopDistance; // The destination is incremented by the hop distance.
							break;

						//If the frog is going right.
						case 3:
							iNextLocation[0] += iHopDistance; // The destination is incremented by the hop distance.
							break;
					}
				}

				//If the position of the frog is not equal to it's destination on the x axis.
				else
				{
					CurrentSprite.setTextureRect(sf::IntRect(25,0,25,25));
					switch(i)
					{
						//If the frog is going left.
						case 2:
							CurrentSprite.setRotation(-90.0f); //Frog is faced left.
							setPosition(getPosition().x - iHopSpeed, getPosition().y); //Frog is moved left by the hop speed.
							break;
						//If the frog is going right.
						case 3:
							CurrentSprite.setRotation(90.0f); //Frog is faced right.
							setPosition(getPosition().x + iHopSpeed, getPosition().y); //Frog is moved right by the hop speed.
							break;
					}

					//If the frog reaches its destination it's movement in the direction is stopped.
					if (getPosition().x == iNextLocation[0])
					{
						ToggleDirection(i , false);
						CurrentSprite.setTextureRect(sf::IntRect(0,0,25,25));
					}
				}
			}
		}
	}

	//Positions the texture.
	CurrentSprite.setPosition(getPosition().x + (getSize().x /2), getPosition().y + (getSize().x /2));

	//The frog's collsion with the window is then checked.
	WindowCollision(iWindowWidth, iWindowHeight);
}

void Frog::StopMove()
{
	//The next location variable is set to the current location
	iNextLocation[0] = getPosition().x;
	iNextLocation[1] = getPosition().y;

	//Then all directions of movement are set to false.
	for(int i = 0; i <= bDirection.size() - 1; i++)
	{
		ToggleDirection(i , false);
	}
}

void Frog::ToggleDirection(int iDirection , bool bToggle)
{
	//Checks to see if the ball is moving in any direction
	bool bMoving = false;
	for(int i = 0; i < bDirection.size() ; i++)
	{
		if (bDirection[i] == true)
		{
			bMoving = true;
		}
	}

	//If the frog is not moving in any direction or the current direction is currently in movement
	if(bMoving == false || bDirection[iDirection] == true)
	{
		//If the direction is within the boundaries.
		if (iDirection < bDirection.size() && iDirection >= 0)
		{
			//The direction is toggled (either enabled or disabled.)
			bDirection[iDirection] = bToggle;
		}
	}
	
}

void Frog::Kill(int& iHighScore)
{
	//Takes a lif off then resets its position to the original position.
	iLives -=1;
	ResetPosition();
	StopMove();

	//If the player has lost all of their lives.
	if (iLives <= 0)
	{
		//Checks to see if the highscore has been beaten if so its overwritten.
		if (iScore > iHighScore)
		{
			iHighScore = iScore;
		}
	}
}
void Frog::ResetPosition()
{
	//Resets the position of the frog.
	setPosition(400, 550);
}

void Frog::WindowCollision(int iWindowWidth, int iWindowHeight)
{
	//Checks if any window collision has occured.
	if(getPosition().y < 0 || getPosition().y + getSize().y > iWindowHeight || getPosition().x < 0 || getPosition().x + getSize().x > iWindowWidth )
	{
		//Checks TOP for collision and if so then sets the position of the frog to the top of the screen.
		if(getPosition().y < 0)
		{
			setPosition(getPosition().x, 0);
		}
		//Checks BOTTOM for collision and if so then sets the position of the frog to the bottom of the screen.
		if(getPosition().y + getSize().y > iWindowHeight)
		{
			setPosition(getPosition().x, iWindowHeight - getSize().y);
		}
		//Checks LEFT for collision and if so then sets the position of the frog to the left of the screen.
		if(getPosition().x < 0)
		{
			setPosition(0, getPosition().y);
		}
		//Checks RIGHT for collision and if so then sets the position of the frog to the right of the screen.
		if(getPosition().x + getSize().x > iWindowWidth)
		{
			setPosition(iWindowWidth - getSize().x, getPosition().y);
		}

		//Stops any movement from the player
		StopMove();
	}
}

bool Frog::Collision(Vehicle& Obj1, int &iHighscore)
{
	//Updates both Collision box coordinates.
	BoundingBox = getGlobalBounds();
	Obj1.BoundingBox = Obj1.getGlobalBounds();

	//If the boxes collide the frog dies.
	if (BoundingBox.intersects(Obj1.BoundingBox))
	{
		Kill(iHighscore);
		return true;
	}
}

bool Frog::Collision(End& Obj1)
{
	//Updates both Collision box coordinates.
	BoundingBox = getGlobalBounds();
	Obj1.BoundingBox = Obj1.getGlobalBounds();

	//If the boxes collide the score values are incremented.
	if (BoundingBox.intersects(Obj1.BoundingBox))
	{
		iScore += 100 * iLevel;
		iLevel += 1;
		ResetPosition();
		StopMove();
		return true;
	}
}

int Frog::getLives()
{
	//Returns the amount of lives.
	return iLives;
}

int Frog::getScore()
{
	//Returns the current score.
	return iScore;
}

int Frog::getLevel()
{
	//Returns the current Level.
	return iLevel;
}