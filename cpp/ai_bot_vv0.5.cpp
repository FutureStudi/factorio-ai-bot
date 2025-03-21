
// Factorio AI Bot - C++ Version v0.5
// Description: Final working version.

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
struct Resource { std::string name; float x, y; float distance; };

const std::vector<std::string> LOG_LOCATIONS = {
    "C:/Users/Lance/AppData/Roaming/Factorio/factorio-current.log",
    "C:/Users/Lance/AppData/Roaming/Factorio/script-output/factorio_ai_data.txt"
};

float calculateDistance(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

Player getPlayerPosition() {
    Player playerPos = {0, 0};
    std::ifstream logFile;
    std::string line;
    std::regex playerPattern(R"(Player Position\]: x=(-?\d+\.\d+), y=(-?\d+\.\d+))");

    for (const auto& filePath : LOG_LOCATIONS) {
        logFile.open(filePath);
        if (!logFile.is_open()) continue;
        while (getline(logFile, line)) {
            std::smatch match;
            if (std::regex_search(line, match, playerPattern)) {
                playerPos.x = std::stof(match[1].str());
                playerPos.y = std::stof(match[2].str());
            }
        }
        logFile.close();
    }
    return playerPos;
}

int main() {
    std::cout << "[DEBUG] AI Bot Version v0.5 Starting..." << std::endl;
    while (true) {
        Player player = getPlayerPosition();
        std::cout << "[DEBUG] Player Position: x=" << player.x << ", y=" << player.y << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    return 0;
}
