#pragma once
/*
Manages the scenes as well as retrieving data from scenes.
*/
#include "Scene.h"
#include "JSONHandler.h"
#include <iostream>
#include <algorithm> //used for shuffling
#include <random> //use for random number generation

using namespace std;

class SceneManager
{
public:
	SceneManager();
	static SceneManager* instance;
	//For AdventureGeneration
	void BuildAdventure(int legnth);

	void LoadScenesFromJSON();
	//For Advancing Game
	void Advance();
	//for forcing scene change to ending state
	void OverrideSceneToIntroduction();
	void OverrideSceneToEnding();
	void OverrideSceneToLandLord();

	//compares player data to option, can probably be moved to a Rules/Conflict static class later
	bool CheckPlayerSuccess(int index, int money, int food, int energy);

	//To Get Information About Game
	vector<int> GetConsequences(int index);
	bool IsLastScene();
	bool IsOptionSpecial(int index);
	char GetResourceType(int index);
	int GetResourceAmmont(int index);
	string GetSceneText();
	string GetTextAtOption(int option);
	string GetResultText(int index, bool success);
	vector<string> GetAllOptionText();

	//for serialization
	std::vector<Scene> GetSceneDictionary();
private:
	//Scene Storage
	static vector<Scene> SceneDictionary; //not actual dictionary, list a vector of scenes
	vector<Scene> SceneQueue; //the scenes that will be navigated during the advenutre

	//Static Scenes that are at the beggining or the end of the game
	Scene currentScene;
	Scene IntroductoryScene;
	Scene LandLordScene;
	Scene LoseScene;

	//Control Variables
	bool isLastScene;
	int sceneIndex = -1;
};