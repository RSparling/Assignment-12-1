#include "Game.h"

Game::Game()
{
	jsonHandler = JSONHandler();
	sceneManager.LoadScenesFromJSON();
	sceneManager.BuildAdventure(10);
}

int Game::Begin()
{
	while (true) {
		//caches initial stats to display
		display.SetPlayerStats(player.GetMoney(), player.GetFood(), player.GetEnergy());
		//override current scene to introduction

		sceneManager.OverrideSceneToIntroduction();
		//pass intro text into display as well as options which should be 0
		PlayIntroduction();

		input.GetInputAny();

		isPlaying = true;
		while (isPlaying) {
			sceneManager.Advance();
			if (!sceneManager.IsLastScene() && !isGameOver)
				PlayScene();
			else if (isGameOver) {
				GameOver();
				if (quitGame)
					return 0;
			}
			else
				LandLord();
		}

		if (quitGame)
			return 0;

		if (doReset && !quitGame)
			ResetGame();

		return 0;
	}
	return 0;
}

void Game::PlayIntroduction()
{
	display.SetScenarioText(sceneManager.GetSceneText());
	display.SetOptionsText(sceneManager.GetAllOptionText());
	display.UpdateScreen();
}

void Game::GetInput() //while loop to get w/s and pass index change to display to update cursor location
{
	while (!input.Confirm()) {
		input.GetInput();
		if (input.Up())
			display.IncrimentCursor();
		else if (input.Down())
			display.DecrimentCursor();
		display.UpdateScreen();
	}
}

void Game::PassTextToDisplay()
{
	//Get text from current scenarior and pass it to display
	display.SetScenarioText(sceneManager.GetSceneText());
	//pass options to display
	display.SetOptionsText(sceneManager.GetAllOptionText());
}

void Game::UpdatePlayerData(bool success)
{
	int _index = display.GetCursorPosition();
	vector<int> _consequences = sceneManager.GetConsequences(_index);
	char _resType = sceneManager.GetResourceType(_index);
	int _cost = sceneManager.GetResourceAmmont(_index);

	player.Modify(_resType, _cost, _consequences, success);
	isGameOver = player.isGameOver();
	display.SetPlayerStats(player.GetMoney(), player.GetFood(), player.GetEnergy());
}

void Game::GameOver() {
	isPlaying = false;
	PassTextToDisplay();
	display.UpdateScreen();
	input.Clear();
	input.GetInput();
	if (input.Confirm()) {
		ResetGame();
		system("cls");
		printf("ResetGame");
		system("pause");
	}
	else if (input.Up() || input.Down()) {
		quitGame = true;
		system("cls");
		printf("Quit Game");
		system("pause");
	}
}

void Game::LandLord()
{
	isPlaying = false;
	sceneManager.OverrideSceneToLandLord();
	bool _isPlayerSuccess = false;
	display.Clear();
	input.Clear(); //makes sure we're not at the end of the list
	PassTextToDisplay();
	display.UpdateScreen();
	GetInput();
	//see if the player is succesful
	_isPlayerSuccess = sceneManager.CheckPlayerSuccess(display.GetCursorPosition(), player.GetMoney(), player.GetFood(), player.GetEnergy());
	//modify player data basd on success
	UpdatePlayerData(_isPlayerSuccess);

	if (_isPlayerSuccess) {
		system("cls");
		printf("Wow dave, you really did it. I didnt expect that. Hit 'e' if you want to pay rent again next month\n");
		printf("or hit the 's' or 'w' key if you want me to help pack up your stuff and kick you out.");

		input.Clear();
		input.GetInput();
		if (input.Confirm()) {
			ResetGame();
		}
		else if (input.Up() || input.Down()) {
			quitGame = true;
		}
	}
	else {
		system("cls");
		printf("Wow dave, you really messed that. I didnt expect that. Hit 'e' if you want another chance next month\n");
		printf("or hit the 's' or 'w' key if you want me to help pack up your stuff and kick you out.");

		input.Clear();
		input.GetInput();
		if (input.Confirm()) {
			ResetGame();
		}
		else if (input.Up() || input.Down()) {
			quitGame = true;
		}
	}
}

void Game::PlayScene()
{
	bool _isPlayerSuccess = false;
	display.Clear();
	input.Clear(); //makes sure we're not at the end of the list
	PassTextToDisplay();
	display.UpdateScreen();
	GetInput();
	//see if the player is succesful
	_isPlayerSuccess = sceneManager.CheckPlayerSuccess(display.GetCursorPosition(), player.GetMoney(), player.GetFood(), player.GetEnergy());
	//modify player data basd on success
	UpdatePlayerData(_isPlayerSuccess);

	//Push the scenario resolution to display
	display.Clear();
	display.SetScenarioText(sceneManager.GetResultText(display.GetCursorPosition(), _isPlayerSuccess));

	//Display
	display.UpdateScreen();
	input.GetInputAny();
}

void Game::ResetGame() // resets entire game
{
	player = *new Player();
	sceneManager = *new SceneManager();
	display = *new Display();
	isPlaying = true;
	doReset = false;
	isGameOver = false;
	quitGame = false;
	sceneManager.BuildAdventure(2);
}