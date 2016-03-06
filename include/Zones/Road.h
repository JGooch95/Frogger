#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Zone.h"
#include "Obstacles/Vehicle.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

class Road : public Zone
{
	private:
		int iLanes;
		int iLaneHeight;

	public:
		Road();
		std::vector<Vehicle> VehicleList;
		void setLanes(int iLanes);
		int getLanes();
};