#pragma once
#include <iostream>
#include <conio.h>
static class Input {
public:
	//Check if this is the key that was hit;
	bool Up() { return up; }
	bool Down() { return down; }
	bool Confirm() { return confirm; }
	void GetInput(); //only w and s are valid inputs
	void GetInputAny(); //any key may be pressed
	void Clear(); //sets all input to false
private:
	//All keys that are checked for
	bool up = false;
	bool down = false;
	bool confirm = false;
};