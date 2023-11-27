#include "Player.h"

Player::Player() {
	ResetPlayer();
}
int Player::GetFood()
{
	return food;
}

int Player::GetEnergy()
{
	return energy;
}

int Player::GetMoney()
{
	return money;
}

bool Player::isGameOver()
{
	return food == 0 || money == 0 || energy == 0;
}

void Player::ResetPlayer()
{
	energy = 3;
	money = 5;
	food = 3;
}

void Player::Modify(char resourceType, int cost, vector<int> consequences, bool success)
{
	if (resourceType == 's') {
		money += consequences[0];
		food += consequences[1];
		energy += consequences[2];
		return;
	}

	if (!success) {
		money -= consequences[0];
		food -= consequences[1];
		energy -= consequences[2];
		return;
	}

	switch (resourceType) {
	case 'm':
		money -= cost;
		return;
	case 'f':
		food -= cost;
		return;
	case 'e':
		energy -= cost;
		return;
	}
}