#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "TextBox.h"

class HUD : public TextBox
{
	public:
		HUD();
		void Draw(int Lives, int Score, int HighScore, int Level);
};