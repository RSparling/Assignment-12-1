#pragma once
#include "SceneManager.h"
#include "Display.h"
#include "Input.h"
#include "Player.h"
#include "JSONHandler.h"
class Game {
public:
	Game();
	int Begin();
private:
	SceneManager sceneManager;
	Display display;
	Input input;
	Player player;
	JSONHandler jsonHandler;

	//used for flow control and state change
	bool isPlaying = false;
	bool isGameOver = false;
	bool quitGame = false;
	bool doReset = false;
	bool continuePlaying = true;

	//used core gameplay loop to bundle frequently used code
	void GetInput();
	void PassTextToDisplay();
	void UpdatePlayerData(bool success);
	void PlayScene();

	//jumps to set scene
	void GameOver();
	void LandLord();
	void PlayIntroduction();

	//resets the game
	void ResetGame();
};