#include "Input.h"

void Input::GetInput()
{
	Clear();
	while (true) {
		char input = _getch();
		if (input == 'w')
		{
			up = true;
			return;
		}
		if (input == 's')
		{
			down = true;
			return;
		}
		if (input == 'e') {
			confirm = true;
			return;
		}
	}
}

void Input::GetInputAny() //preferable over system("pause") since there is no text displayed
{
	char input = _getch();
}

void Input::Clear()
{
	std::cin.clear();
	up = false;
	down = false;
	confirm = false;
}