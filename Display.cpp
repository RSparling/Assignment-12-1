#include "Display.h"

Display::Display()
{
	cursorPosition = 0;
	cursorMax = 0;
}

void Display::SetScenarioText(string text)
{
	mainText = text;
}

void Display::SetOptionsText(vector<string> text)
{
	cursorPosition = 0;
	optionsText = text;
	cursorPosition = 0;
	cursorMax = text.size();
}

void Display::UpdateScreen() { //update the visuals on the screen
	system("cls");
	DisplayPlayerStats();

	cout << mainText;

	int index = -1;
	cout << endl << endl;
	for (string text : optionsText) {
		index += 1; //this is have it at 0 if there is at least one option, prevents from trying to print out null or empty strings
		if (cursorPosition == index)
			cout << '>' + optionsText[index] << endl;
		else
			cout << optionsText[index] << endl;
	}
}

void Display::IncrimentCursor()
{
	cursorPosition -= 1;
	if (cursorPosition < 0)
		cursorPosition = cursorMax - 1;
}

void Display::DecrimentCursor()
{
	cursorPosition += 1;
	if (cursorPosition > cursorMax - 1)
		cursorPosition = 0;
}

void Display::SetPlayerStats(int money, int food, int energy)
{
	this->money = money;
	this->food = food;
	this->energy = energy;
}

void Display::Clear()
{
	mainText = "";
	optionsText.clear();
}

int Display::GetCursorPosition()
{
	return cursorPosition;
}

void Display::DisplayPlayerStats() {//Displays player stats at the top of the screen
	printf("_________________________________\n");
	printf("|Money: %i|Food: %i|Energy: %i|\n", money, food, energy);
	printf("_________________________________\n");
}