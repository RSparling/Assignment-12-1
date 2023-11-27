#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Display {
public:
	Display();
	//passes text for display
	void SetScenarioText(string text);
	void SetOptionsText(vector<string> text);

	//print to screen
	void UpdateScreen();

	//cursor control
	void IncrimentCursor();
	void DecrimentCursor();

	//passes player stats to be displayed
	void SetPlayerStats(int money, int food, int energy);

	//clear the screen
	void Clear();

	//gets which option the cursor is on
	int GetCursorPosition();
private:
	string mainText;
	vector<string> optionsText;
	int cursorPosition;
	int cursorMax;
	int money;
	int food;
	int energy;
	void DisplayPlayerStats();
};