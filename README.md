# Factorio AI Bot 🤖

This project is an AI assistant for the game [Factorio](https://www.factorio.com/). It reads game logs to analyze player position and nearby resources, then simulates movement using external automation techniques.

---

## 🧠 Project Overview

The AI bot consists of two major components:

### 1. 🧩 Factorio Mod
- Logs player position and resource data every 5 seconds.
- Outputs data to:
  - `factorio-current.log` (via `log()`)
  - In-game console (via `game.print()`)

### 2. 🧠 C++ AI Script
- Parses `factorio-current.log` and `factorio_ai_data.txt`
- Extracts:
  - Player position
  - Resource positions with names
- Selects the **highest priority resource** and moves the player toward it.

---

## 🔁 AI Logic Flow

1. Read latest log lines.
2. Parse player and resource data using regex.
3. Rank resources by:
   - `score = priority / distance`
4. Choose the best target.
5. Simulate movement input (`W`, `A`, `S`, `D`) toward that resource.

---

## 🔧 Current Limitations

- Input simulation using `SendInput`, `PostMessage`, and `AttachThreadInput` does **not currently move the player** in Factorio due to input blocking.
- External input drivers (e.g., vJoy, Interception) may be required for full automation.

---

## 🗂️ Project Structure

```
factorio-ai-bot/
├── cpp/                    # C++ AI scripts
│   ├── ai_bot_vv0.1.cpp
│   ├── ...
│   └── ai_bot_vv0.6.cpp
├── mod/                    # Factorio mod files
│   └── factorio_ai_bot_0.4.3.zip
├── docs/
│   └── Factorio_AI_Bot_Combined_Documentation.txt
└── README.md
```

---

## 🚧 Version History

- `v0.1` – Basic log parsing
- `v0.4` – Reads both log sources
- `v0.5` – Extracts player & resource data
- `v0.6` – Implements prioritization + movement logic (input methods under testing)

---

## 📌 Next Steps

- Explore raw input injection using external libraries
- Build a basic Web UI for live AI state monitoring
- Add smarter pathfinding or terrain analysis

---

## 📜 License

MIT or custom license — add yours here.