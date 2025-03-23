// Factorio AI Bot - C++ Version v0.6
// Description: Functional resource targeting and basic 1-step movement using scan codes.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cmath>
#include <thread>
#include <chrono>
#include <Windows.h>

struct Player { float x, y; };
struct Resource {
    std::string name{};
    float x = 0.0f;
    float y = 0.0f;
    float distance = 0.0f;
    int priority = 0;
};

const std::vector<std::string> LOG_LOCATIONS = {
    "C:/Users/Lance/AppData/Roaming/Factorio/factorio-current.log",
    "C:/Users/Lance/AppData/Roaming/Factorio/script-output/factorio_ai_data.txt"
};

float calculateDistance(float x1, float y1, float x2, float y2) {
    return static_cast<float>(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

int getResourcePriority(const std::string& name) {
    if (name == "coal") return 4;
    if (name == "iron-ore") return 3;
    if (name == "copper-ore") return 2;
    if (name == "stone") return 1;
    return 0;
}

Player getPlayerPosition() {
    Player playerPos = {0, 0};
    std::regex playerPattern(R"(\[AI Player Position\]: x=(-?\d+\.\d+), y=(-?\d+\.\d+))");
    for (const auto& filePath : LOG_LOCATIONS) {
        std::ifstream logFile(filePath);
        if (!logFile.is_open()) continue;
        std::vector<std::string> lines;
        std::string line;
        while (getline(logFile, line)) {
            lines.push_back(line);
        }
        logFile.close();

        for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
            std::smatch match;
            if (std::regex_search(*it, match, playerPattern)) {
                playerPos.x = std::stof(match[1].str());
                playerPos.y = std::stof(match[2].str());
                return playerPos;
            }
        }
    }
    return playerPos;
}

// Placeholder for rest of v0.6 code...