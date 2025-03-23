// Factorio AI Bot - C++ Version v0.8
// Description: Adds resource analysis, vision-based mouse alignment, and separate movement/mining logic.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cmath>
#include <thread>
#include <chrono>
#include <Windows.h>
#include <gdiplus.h>
#include <opencv2/opencv.hpp>
#pragma comment (lib,"Gdiplus.lib")

using namespace Gdiplus;

// Initialize GDI+ for capturing window screenshots
class GDIPlusManager {
public:
    GDIPlusManager() { GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr); }
    ~GDIPlusManager() { GdiplusShutdown(gdiplusToken); }
private:
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
};

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
        while (getline(logFile, line)) lines.push_back(line);
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

std::vector<Resource> getResources(const Player& player) {
    std::vector<Resource> resources;
    std::regex resourcePattern(R"(\[AI Data Chunk\]: name=\"(\w+)\", position=\{x=(-?\d+\.\d+), y=(-?\d+\.\d+)\})");
    for (const auto& filePath : LOG_LOCATIONS) {
        std::ifstream logFile(filePath);
        if (!logFile.is_open()) continue;
        std::string line;
        while (getline(logFile, line)) {
            std::smatch match;
            if (std::regex_search(line, match, resourcePattern)) {
                Resource res;
                res.name = match[1];
                res.x = std::stof(match[2].str());
                res.y = std::stof(match[3].str());
                res.priority = getResourcePriority(res.name);
                if (res.priority > 0) resources.push_back(res);
            }
        }
        logFile.close();
    }
    return resources;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    wchar_t title[256];
    GetWindowTextW(hwnd, title, sizeof(title)/sizeof(wchar_t));
    std::wstring windowTitle(title);
    if (windowTitle.find(L"Factorio") != std::wstring::npos) {
        HWND* result = reinterpret_cast<HWND*>(lParam);
        *result = hwnd;
        return FALSE;
    }
    return TRUE;
}

HWND getFactorioWindow() {
    HWND hwnd = nullptr;
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&hwnd));
    return hwnd;
}

void pressKeyToWindow(HWND hwnd, WPARAM key) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = 0;
    input.ki.wScan = MapVirtualKeyA(key, MAPVK_VK_TO_VSC);
    input.ki.dwFlags = KEYEVENTF_SCANCODE;
    input.ki.dwExtraInfo = 0;
    input.ki.time = 0;

    INPUT input_up = input;
    input_up.ki.dwFlags |= KEYEVENTF_KEYUP;

    SendInput(1, &input, sizeof(INPUT));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    SendInput(1, &input_up, sizeof(INPUT));
}

void moveToTarget(const Player& player, const Resource& target) {
    HWND hwnd = getFactorioWindow();
    if (!hwnd) {
        std::cout << "[WARN] Could not find Factorio window." << std::endl;
        return;
    }

    float dx = target.x - player.x;
    float dy = target.y - player.y;
    float distance = calculateDistance(player.x, player.y, target.x, target.y);

    if (distance < 1.0f) {
        std::cout << "[INFO] Already close to target, no movement needed." << std::endl;
        return;
    }

    int steps = (std::min)(static_cast<int>(distance), 5);

    if (fabs(dx) > 1.0f && fabs(dy) > 1.0f) {
        if (dx > 0) for (int i = 0; i < steps; ++i) pressKeyToWindow(hwnd, 'D');
        else for (int i = 0; i < steps; ++i) pressKeyToWindow(hwnd, 'A');

        if (dy > 0) for (int i = 0; i < steps; ++i) pressKeyToWindow(hwnd, 'S');
        else for (int i = 0; i < steps; ++i) pressKeyToWindow(hwnd, 'W');
    } else if (fabs(dx) > fabs(dy)) {
        if (dx > 0) for (int i = 0; i < steps; ++i) pressKeyToWindow(hwnd, 'D');
        else for (int i = 0; i < steps; ++i) pressKeyToWindow(hwnd, 'A');
    } else {
        if (dy > 0) for (int i = 0; i < steps; ++i) pressKeyToWindow(hwnd, 'S');
        else for (int i = 0; i < steps; ++i) pressKeyToWindow(hwnd, 'W');
    }
}

void mineAtPosition(const Resource& target, const Player& player) {
    float distance = calculateDistance(player.x, player.y, target.x, target.y);
    if (distance > 5.0f) {
        std::cout << "[INFO] Target too far to mine. Distance: " << distance << std::endl;
        return;
    }

    int screenX = 1920;
    int screenY = 1080;
    const float pixelsPerTile = 32.0f;
    float dx = target.x - player.x;
    float dy = target.y - player.y;
    int offsetX = static_cast<int>(dx * pixelsPerTile);
    int offsetY = static_cast<int>(dy * pixelsPerTile);
    SetCursorPos(screenX + offsetX, screenY + offsetY);

    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
    std::this_thread::sleep_for(std::chrono::seconds(2));
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
    std::cout << "[ACTION] Mining at position: (" << target.x << ", " << target.y << ")" << std::endl;
}

void captureFactorioScreenshot(HWND hwnd, const std::wstring& filename) {
    HDC hdcScreen = GetDC(NULL);  // Full desktop
    HDC hdcMemDC = CreateCompatibleDC(hdcScreen);

    int screenX = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    int screenY = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    int originX = GetSystemMetrics(SM_XVIRTUALSCREEN);
    int originY = GetSystemMetrics(SM_YVIRTUALSCREEN);

    HBITMAP hbmScreen = CreateCompatibleBitmap(hdcScreen, screenX, screenY);
    SelectObject(hdcMemDC, hbmScreen);

    BitBlt(hdcMemDC, 0, 0, screenX, screenY, hdcScreen, originX, originY, SRCCOPY);

    Gdiplus::Bitmap bitmap(hbmScreen, nullptr);
    CLSID pngClsid;
    CLSIDFromString(L"{557CF406-1A04-11D3-9A73-0000F81EF32E}", &pngClsid);
    bitmap.Save(filename.c_str(), &pngClsid, nullptr);

    DeleteObject(hbmScreen);
    DeleteDC(hdcMemDC);
    ReleaseDC(NULL, hdcScreen);
}

int main() {
    std::cout << "[INFO] Waiting 3 seconds... Switch to Factorio." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    GDIPlusManager gdiplus;
    std::cout << "[DEBUG] AI Bot Version v0.8 Starting..." << std::endl;

    HWND hwnd = getFactorioWindow();
    if (!hwnd) {
        std::cout << "[ERROR] Could not find Factorio window." << std::endl;
        return 1;
    }

    std::wstring screenshotPath = L"C:/Users/Lance/Documents/FactorioVision/factorio_ai_screen.png";
    captureFactorioScreenshot(hwnd, screenshotPath);
    std::cout << "[INFO] Screenshot captured." << std::endl;

    cv::Mat haystack = cv::imread("C:/Users/Lance/Documents/FactorioVision/factorio_ai_screen.png", cv::IMREAD_COLOR);
    std::vector<std::string> templatePaths;
    for (int i = 1; i <= 64; ++i) {
        templatePaths.push_back("C:/Users/Lance/Documents/FactorioVision/coal_template_" + std::to_string(i) + ".png");
    }

    if (haystack.empty()) {
        std::cerr << "[ERROR] Could not load screenshot." << std::endl;
        return 1;
    }

    double bestScore = 0.0;
    cv::Point bestLoc;
    cv::Mat bestNeedle;

    for (const auto& path : templatePaths) {
        cv::Mat needle = cv::imread(path, cv::IMREAD_COLOR);
        if (needle.empty()) continue;

                cv::Mat result;
        cv::matchTemplate(haystack, needle, result, cv::TM_CCOEFF_NORMED);
        double minVal, maxVal;
        cv::Point minLoc, maxLoc;
        cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
        if (maxVal < 0.3) continue;

        if (maxVal > bestScore) {
            bestScore = maxVal;
            bestLoc = maxLoc;
            bestNeedle = needle;
        }
    }

    if (bestScore < 0.5) {
        std::cerr << "[WARN] No good match found. Confidence: " << bestScore << std::endl;
        return 1;
    }

    cv::rectangle(
        haystack,
        bestLoc,
        cv::Point(bestLoc.x + bestNeedle.cols, bestLoc.y + bestNeedle.rows),
        cv::Scalar(0, 0, 255),
        2
    );
    cv::imwrite("C:/Users/Lance/Documents/FactorioVision/match_debug.png", haystack);

    std::cout << "[MATCH] Coal found at screen coordinates: (" << bestLoc.x << ", " << bestLoc.y << ")" << std::endl;

    return 0;
}
