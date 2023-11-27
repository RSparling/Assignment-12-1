#pragma once
#include <vector>
using std::vector;
class Player
{
public:
	Player();
	//Getters
	int GetFood();
	int GetEnergy();
	int GetMoney();

	//Checks if the player is dead
	bool isGameOver();

	//resets the player
	void ResetPlayer();

	//modify the player based on the option and results, can probably be moves to a an external class
	void Modify(char resourceType, int cost, vector<int> consequences, bool success);
private:
	//player resources
	int food;
	int money;
	int energy;
};
