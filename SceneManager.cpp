#include "SceneManager.h"

/*
notes for scene bilding
resource codes:
m - money
f - food
e - energy
s - special, will always succeed and add to player stats
*/
//Builds initial scenes
SceneManager* SceneManager::instance = nullptr;
std::vector<Scene> SceneManager::SceneDictionary;
SceneManager::SceneManager()
{
	instance = this;
	
	//builds only static scenes with the rest being built by the json handler

	LandLordScene = Scene(
		"We made it dave!Now to pay the landlord the money!"
	)
		.AddOption(Option(
			"Pay the Landlord rent.",
			"Wow Dave, we made it! And luckily we made some extra cash along the way or you wouldn't have been able to pay\n"
			"your share of the rent. Good job, now we can do this next month where you'll hopefully mess up less.\n",
			"Dave, is that wallet empty? I can't beleive you dont have the money for rent. You had one job Dave, one job. I am\n"
			"extremely dissapointed in you. Let's go back to the flat and start packing so we're ready when the eviction ferret\n"
			"shows up.",
			'm', 6, 0, 0, 0
		))
		.AddOption(Option(
			"Fight the Landlord",
			"Dave, put him down dave. No, dont do that! Put down the street sign! Oh wow, you actually won. I'm surprised."
			"Good job Dave, now we never have to pay rent again!\n",
			"Dave, what are you-! No, Dave! You fool, you shouldn't be fighting barehanded! Maybe if you got that knife from\n"
			"the squirrel you would have had a chance! Well, I guess it's time to find a new schmuck to pay for rent.",
			'e', 6, 0, 0, 0
		))
		.AddOption(Option(
			"Offer the LandLord snacks",
			"Wow Dave, you manage to have him defer rent untill next month by bribing him with food. I didnt expect that to\n"
			"work but here we are. Huh.",
			"Dave, why would he defer rent just because you offered him a twinkie, an old mint and some used gum? Now he's\n"
			"going to evict us because you decided to keep messing around. Great job.",
			'f', 6, 0, 0, 0
		)
		);

	LoseScene = *new Scene(
		"Dave, what's wrong? Oh no dave, you ruined everything! You really are useless, arent you?"
	);

	IntroductoryScene = *new Scene(
		"In a world of crazed animals and utter absurdity you live with dead beat room mates who refuse to help pay rent.\n"
		"While Chris and Mike bumb around it looks like it's up to you, Dave, to track down our landlord and give him our\n"
		"rent payment. I have faith in you Dave. Press any key to continue your adventure.\n\n"
		"What's that, where's my part of the rent? I'm sorry, I'm a bit short. Here, how about I narrorate your entire   \n"
		"adventure and tell you how to play. Press 'w' and 's' to navigate options and 'e' to confirm. Now confirm so we \ncan get going.");
}

//get the main text for the scene
string SceneManager::GetSceneText()
{
	string _text = currentScene.GetText();
	return _text;
}

//get text for specific option
string SceneManager::GetTextAtOption(int index) {
	vector<Option> _options;
	_options = currentScene.GetOptions();
	string _text = _options[index].GetOptionText();
	return _text;
}

//returns text for all option choices.
vector<string> SceneManager::GetAllOptionText()
{
	vector<string> _options;
	vector<Option> _sceneOptions = currentScene.GetOptions();

	for (Option o : _sceneOptions) {
		_options.push_back(o.GetOptionText());
	}

	return _options;
}

std::vector<Scene> SceneManager::GetSceneDictionary()
{
	return SceneDictionary;
}

//set current scene to intro scene
void SceneManager::OverrideSceneToIntroduction()
{
	currentScene = IntroductoryScene;
}

//set current scene to end scene
void SceneManager::OverrideSceneToEnding()
{
	currentScene = LoseScene;
}

void SceneManager::OverrideSceneToLandLord()
{
	currentScene = LandLordScene;
}

//shuffles the scenes and builds the adventure.
void SceneManager::BuildAdventure(int legnth)
{
	int remainingScenesToAdd = legnth;

	auto rng = std::default_random_engine{};// Gets random numbers;
	for (; remainingScenesToAdd > 0; remainingScenesToAdd--) {
		std::shuffle(std::begin(SceneDictionary), std::end(SceneDictionary), rng);
		SceneQueue.push_back(SceneDictionary[0]);
	}
}

void SceneManager::LoadScenesFromJSON()
{
	SceneDictionary = JSONHandler::instance->deseiralizeScenes();
}

//proceed to the next scene, if its the end go to the end scene
void SceneManager::Advance()
{
	if (isLastScene)
		return;
	sceneIndex += 1;
	if (sceneIndex == SceneQueue.size() - 1)
	{
		currentScene = LoseScene;
		isLastScene = true;
		return;
	}
	currentScene = SceneQueue[sceneIndex];
}

bool SceneManager::IsLastScene() {
	return isLastScene;
}

//only checks if the player passes
bool SceneManager::CheckPlayerSuccess(int index, int money, int food, int energy)
{
	Option option = currentScene.GetOption(index);
	char reqResource = option.GetRequiredResource();
	int reqAmmount = option.GetRequiredAmmount();

	switch (reqResource) {
	case 'f':
		if (food - reqAmmount > 0)
			return true;
		return false;
	case 'm':
		if (money - reqAmmount > 0)
			return true;
		return false;
	case 'e':
		if (energy - reqAmmount > 0)
			return true;
		return false;
	case 's':
		return true;
	default:
		system("cls");
		printf("An error had occured, unexpeded required resource of code: " + reqResource);
		return true;
	}
}

vector<int> SceneManager::GetConsequences(int index)
{
	return currentScene.GetOption(index).GetConsequences();
}

bool SceneManager::IsOptionSpecial(int index)
{
	Option _option = currentScene.GetOption(index);
	if (_option.IsSpecial())
		return true;
	return false;
}

char SceneManager::GetResourceType(int index) {
	Option _option = currentScene.GetOption(index);
	return _option.GetRequiredResource();
}

int SceneManager::GetResourceAmmont(int index) {
	Option _option = currentScene.GetOption(index);
	return _option.GetRequiredAmmount();
}

string SceneManager::GetResultText(int index, bool success)
{
	Option _option = currentScene.GetOption(index);
	if (success)
		return _option.GetSuccessText();

	return _option.GetFailText();
}