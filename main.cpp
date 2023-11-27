/*
Name: Russell Sparling
CSC 215
Assignment 12.1

Notes for the Instructor:
As per the assignment this is a continuation of Assignment 6.1. A link to the repository is provided as a comment.

The main addition is the JsonHandler which is used to serialize and deserialize the scenes. This is done using the nlohmann json library.
In order to allow serialization the struct Option and Scene was modified to include a to_json() and from_json function.

I know this assignment is not about serialization or the file stream however the original assignment alraedy fufilled
the requirements for this assignment. I did the file stream as it both adds to the original intent of the assignment of
working with multiple source files and took the opurtunity to learn about both serializatoin and file streams.
*/

#include<iostream>
#include <windows.h>
#include "Game.h"

string workingDirectory;

int main() {
	Game game;
	game.Begin();
	return 0;
}