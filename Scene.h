#pragma once
#include <nlohmann/json.hpp>
/*
Defines Scenes and Options to allow for easy use elsewhere.
*/
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Option {
public:
	Option() {};
	Option(const string& text, const string& success, const string& fail, char requiredResource, int requiredAmmount, int money, int food, int energy)
		: text(text), successText(success), failureText(fail), requiredResource(requiredResource), requiredAmmount(requiredAmmount), money(money), food(food), energy(energy)
	{
	}

	string GetOptionText() {
		return text;
	}

	string GetSuccessText() {
		return successText;
	}

	string GetFailText() {
		return failureText;
	}

	char GetRequiredResource() {
		return requiredResource;
	}

	char GetRequiredAmmount() {
		return requiredAmmount;
	}

	bool IsSpecial() {
		if (requiredResource == 's')
			return true;
		return false;
	}
	vector<int> GetConsequences() {
		vector<int> consequences;
		consequences.push_back(energy);
		consequences.push_back(food);
		consequences.push_back(money);
		return consequences;
	}
	void from_Json(const nlohmann::json& j);

	nlohmann::json to_json() const {
		return nlohmann::json{
			{"Text", text},
			{"Success", successText},
			{"Fail", failureText},
			{"Resource", std::string(1, requiredResource)},
			{"Required", requiredAmmount},
			{"Money", money},
			{"Food", food},
			{"Energy", energy}
		};
	}
private:
	//the text displayed for the option
	string text;
	string successText;
	string failureText;
	char requiredResource;
	int requiredAmmount;
	//consequences, a +/- to the player current resources
	int money;
	int food;
	int energy;
};

struct Scene {
public:
	//intialize with assignment constructor list
	Scene(string text) :text(text) {}
	Scene() {};
	Scene AddOption(Option option) {//allows a build pattern to be used to add options;
		options.push_back(option);
		return *this;
	}

	string GetText() {
		return text;
	}

	vector<Option> GetOptions() {
		return options;
	}

	Option GetOption(int index) {
		return options[index];
	}
	void from_Json(const nlohmann::json& j);

	nlohmann::json to_json() const {
		nlohmann::json jOptions = nlohmann::json::array();
		for (const auto& option : options) {
			jOptions.push_back(option.to_json());
		}

		return nlohmann::json{
			{"Text", text},
			{"Options", jOptions}
		};
	}
private:
	string text;
	vector<Option> options;
};