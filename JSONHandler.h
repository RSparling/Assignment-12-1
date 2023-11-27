#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Scene.h"
#include <iostream>
#include "SceneManager.h"
using json = nlohmann::json;
/*<summary>
This class handles the serialization and deserialization of the scenes.
</summary>*/
class JSONHandler
{
public:
	//returns the instance of the JSONHandler
	JSONHandler();
	//returns the instance of the JSONHandler
	static JSONHandler* instance;
	std::vector<Scene> deseiralizeScenes();
	void serializeScenes();
private:
	string workingDirectory;
};
