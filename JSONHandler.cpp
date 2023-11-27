#include "JSONHandler.h"

// Static instance pointer initialization to nullptr
JSONHandler* JSONHandler::instance = nullptr;

// Constructor for JSONHandler
JSONHandler::JSONHandler()
{
    instance = this; // Setting the static instance to the current object

    DWORD bufferSize = MAX_PATH;
    std::vector<wchar_t> buffer(bufferSize);

    // Get the full path name of the executable
    if (GetModuleFileName(NULL, buffer.data(), bufferSize)) {
        std::string exePath(buffer.begin(), buffer.end());
        // Truncate the path to get the directory
        size_t pos = exePath.find_last_of("\\/");
        exePath = exePath.substr(0, pos);
        workingDirectory = exePath; // Store the directory of the executable
    }
}

// Function to deserialize scenes from a JSON file
std::vector<Scene> JSONHandler::deseiralizeScenes() {
    cout << "Deserializing Scenes" << endl;

    // Open the Scenes.json file
    std::ifstream file("Scenes.json");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open Scene.json" << endl;
        return std::vector<Scene>(); // Return an empty vector on failure
    }

    nlohmann::json j; // JSON object
    try {
        file >> j; // Parse the JSON from file
    }
    catch (const std::exception& e) {
        std::cerr << "JSON Parsing Error: " << e.what() << endl;
        return std::vector<Scene>(); // Return an empty vector on parsing error
    }

    // Validate the JSON structure
    if (!j.contains("scenes") || !j["scenes"].is_array()) {
        std::cerr << "Invalid JSON format: 'scenes' key not found or not an array" << endl;
        return std::vector<Scene>(); // Return an empty vector on invalid JSON
    }

    std::vector<Scene> scenes; // Vector to hold deserialized scenes
    std::cout << "Converting to Scenes" << endl;

    // Iterate over each scene in the JSON array
    for (const auto& s : j["scenes"]) {
        try {
            Scene scene;
            scene.from_Json(s); // Convert JSON to Scene object
            scenes.push_back(scene); // Add the scene to the vector
        }
        catch (const std::exception& e) {
            std::cerr << "Error processing scene: " << e.what() << endl;
            // Continue processing other scenes even if one fails
        }
    }
    cout << "Number of Scenes: " << scenes.size() << endl;
    std::cout << "Done" << endl;
    return scenes; // Return the vector of deserialized scenes
}

// Function to serialize scenes into a JSON file
void JSONHandler::serializeScenes()
{
    std::cout << "Serializing Scenes" << endl;
    nlohmann::json jScenes = nlohmann::json::array(); // JSON array for storing scenes

    std::vector<Scene> scenes = SceneManager::instance->GetSceneDictionary();
    std::cout << "Number of Scenes: " << scenes.size() << endl;

    // Iterate over each scene and convert to JSON
    for (const auto& scene : scenes) {
        jScenes.push_back(scene.to_json()); // Convert Scene to JSON and add to array
        std::cout << "Scene Added" << endl;
    }

    nlohmann::json j = { {"scenes", jScenes} }; // JSON object with scenes array

    // Write the JSON object to file
    std::cout << "Writing to file" << endl;
    std::ofstream file("Scenes.json");
    file << j.dump(4); // Serialize JSON with 4 spaces indentation
    std::cout << "Done" << endl;
}
