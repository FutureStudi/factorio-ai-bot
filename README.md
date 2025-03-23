# Factorio AI Bot 🤖

A C++ bot for automating player movement and mining in Factorio by combining log file reading and computer vision detection.

## 🔧 Features

### Movement + Mining
- Reads player position and resource positions from Factorio logs.
- Prioritizes resources (coal > iron > copper > stone).
- Simulates WASD movement toward nearby resources.
- Mines when within 5 tiles using mouse input (simulated left click).

### Vision System (WIP)
- Captures the full desktop screen using GDI.
- Uses OpenCV template matching to locate coal resources on screen.
- Loops through up to 64 coal tile templates for matching.
- Draws a red box on the detected coal tile in `match_debug.png`.

## 📂 File Structure

- `coal_template_X.png`: Template images for matching.
- `factorio_ai_screen.png`: Screenshot of the current desktop view.
- `match_debug.png`: Output screenshot with detected coal marked.
- `ai_bot.cpp`: Main AI logic script.
- `README.md`, `CHANGELOG.md`: Project info and version history.

## 🔁 How to Run

1. Run Factorio in windowed/borderless mode with coal on screen.
2. Run the AI bot EXE as Administrator.
3. The bot will:
    - Wait 3 seconds
    - Capture the desktop
    - Attempt coal detection using OpenCV
    - Print the best match location and draw it

## 🧪 Testing Tips

- Ensure camera is zoomed to default.
- Coal must be visible and not covered by UI.
- Match confidence thresholds can be tuned in code.
- Use `match_debug.png` to verify accuracy.

## 🛠 Requirements

- OpenCV 4.11.0 with Debug libraries (e.g., `opencv_world4110d.dll`)
- C++17+
- Windows 10/11
- GDI enabled

## 🚧 In Progress

- Vision-based resource matching
- Inventory checks and management
- Visual UI or override system
- Support for additional resource types