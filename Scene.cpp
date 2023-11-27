#include "Scene.h"

//converts from json to option
void Option::from_Json(const nlohmann::json& j)
{
	//std::cout << "Option JSON: " << j.dump(4) << endl;

	//std::cout << "Parsing Option" << endl;
	//std::cout << "Parsing Energy" << endl;
	// ... Repeat for other fields like Money, Required, etc. ...
	if (j.contains("Energy") && j["Energy"].is_number_integer()) {
		energy = j["Energy"].get<int>();
	}
	else {
		energy = 0; // Default to 0
	}

	//std::cout << "Parsing Fail" << endl;
	if (j.contains("Fail") && j["Fail"].is_string()) {
		failureText = j["Fail"].get<std::string>();
	}
	else {
		failureText = "default fail message"; // Default message
	}

	//std::cout<<"Parsing Money"<<endl;
	if (j.contains("Money") && j["Money"].is_number_integer()) {
		money = j["Money"].get<int>();
	}
	else
	{
		money = 0; // Default to 0
	}
	//std::cout<<"Parsing Required"<<endl;
	if (j.contains("Required") && j["Required"].is_number_integer()) {
		requiredAmmount = j["Required"].get<int>();
	}
	else {
		requiredAmmount = 0; // Default to 0
	}
	//std::cout<<"Parsing Food"<<endl;
	if (j.contains("Food") && j["Food"].is_number_integer()) {
		food = j["Food"].get<int>();
	}
	else {
		food = 0; // Default to 0
	}
	//std::cout<<"Parsing Resource"<<endl;
	if (j.contains("Resource") && j["Resource"].is_string()) {
		requiredResource = j["Resource"].get<std::string>()[0];
	}
	else {
		requiredResource = 'd'; // Some default character
	}
	//std::cout<<"Parsing Success"<<endl;
	if (j.contains("Success") && j["Success"].is_string()) {
		successText = j["Success"].get<std::string>();
	}
	else {
		successText = "default success message"; // Default message
	}
	//std::cout<<"Parsing Text"<<endl;
	if (j.contains("Text") && j["Text"].is_string()) {
		text = j["Text"].get<std::string>();
	}
	else {
		text = "default option text"; // Default message
	}
}

//converts from json to object
void Scene::from_Json(const nlohmann::json& j)
{
	try {
		text = j.value("Text", "default scene text");

		if (j.contains("Options") && j["Options"].is_array()) {
			for (const auto& optionJson : j["Options"]) {
				try {
					Option option;
					option.from_Json(optionJson);
					options.push_back(option);
				}
				catch (const std::exception& e) {
					std::cerr << "Error processing an option in scene: " << e.what() << endl;
					// Decide how to handle this - skip this option, default it, etc.
				}
			}
		}
		else {
			std::cerr << "Missing or invalid 'Options' in scene" << endl;
			// Handle the missing or invalid 'Options'
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error processing Scene: " << e.what() << endl;
		// Handle the exception as needed
	}
}