#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Obstacle.h"

class Vehicle : public Obstacle
{
	public:
		Vehicle();
		Vehicle(int iWidth, int iHeight, std::string sTex);
};