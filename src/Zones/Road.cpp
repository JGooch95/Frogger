#include "Zones/Road.h"

Road::Road()
{
	//Sets the lane settings for the road.
	iLaneHeight = 25;
	iLanes = 6;
	setLanes(iLanes);

	//Applying the values to the rectangular space
	setPosition(getPosition().x , 300);
	setSize(sf::Vector2f(getSize().x , 200));
	setFillColor(sf::Color(60,60,60,255));
}

void Road::setLanes(int iNewLanes)
{
	//Sets the lane count to the new amount of lanes.
	iLanes = iNewLanes;

	//If the list of vehicles is larger than the amount of lanes
	if (VehicleList.size() > iLanes)
	{
		for (int i = VehicleList.size() - 1; iLanes = VehicleList.size(); i-- )
		{
			VehicleList.pop_back();
		}
	}

	//Declares the 2 randomise variables to hold random numbers.
	int iRandom;
	int iRandomVehicle;

	//sets the size of the road according to the amount of lanes.
	setSize(sf::Vector2f(getSize().x , iLaneHeight*iLanes));

	//For every lane.
	for(int i = 0; i < iLanes; i++)
	{
		//Randomise aa vehicle type
		iRandomVehicle = (rand() % 2);

		//If the value is 0 add a lorry to the list of vehicles
		if (iRandomVehicle == 0)
		{
			VehicleList.push_back(Vehicle(100 , 25, "Assets/Sprites/Lorry.png"));
		}

		//If the value is anything else add a car to the list of vehicles
		else
		{
			VehicleList.push_back(Vehicle(40 , 25, "Assets/Sprites/Car.png"));
		}

		//Sets the x any y value of the vehicle added dependant on its lane position.
		VehicleList[i].setY (getPosition().y + (iLaneHeight * i));
		VehicleList[i].setX (i*20);

		//Alternates the direction of the cars every lane.
		if (i % 2 == 0)
		{
			VehicleList[i].setDirection(4);
		}

		//Randomises a movespeed for the vehicle.
		iRandom = (rand() % 5) + 3;
		VehicleList[i].setMoveSpeed(iRandom);
	}

}

int Road::getLanes()
{
	//Returns the amount of lanes.
	return iLanes;
}