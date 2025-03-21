# 🧩 Factorio AI Bot Mod – Structure & Design

This document explains the internal structure of the **Factorio AI Bot mod** and how it interacts with the game and external tools.

---

## 📁 Mod Folder Layout

Each versioned mod folder (e.g., `factorio_ai_bot_0.4.3`) typically includes:

```
factorio_ai_bot_0.x.x/
├── control.lua           # Main logic script executed in-game
├── info.json             # Mod metadata (name, version, author, etc.)
├── locale/
│   └── en/
│       └── locale.cfg    # Optional UI/localization entries
├── README.txt            # Optional instructions
```

---

## 🧠 Key File Descriptions

### `info.json`
Defines metadata for Factorio to load the mod. Example fields:
```json
{
  "name": "factorio_ai_bot",
  "version": "0.4.3",
  "title": "Factorio AI Bot",
  "author": "Creater",
  "factorio_version": "2.0.41",
  "description": "An AI bot for automation in Factorio",
  "dependencies": ["base >= 2.0.41"]
}
```

### `control.lua`
The core logic for the AI mod. Key elements include:

- `script.on_event(defines.events.on_tick, function(event))`
  - Executes code every `X` ticks (e.g., every 5 seconds)

- **Data Output:**
  - Logs player position and nearby resource entities
  - Uses `log()` for `factorio-current.log`
  - Uses `game.print()` for in-game debug messages
  - Old versions used `game.write_file()` (now deprecated and removed)

- **Global State:**
  - Uses `global.ai_log` to store and trim log data
  - Initialized in `script.on_init()` and `script.on_load()`

---

## 🔗 Interaction with External Tools

The mod is designed to work with an external **C++ AI bot** which reads:

- `factorio-current.log` → via `log()`
- (Optional) `factorio_ai_data.txt` → legacy versions

The AI bot makes decisions and attempts to simulate movement outside Factorio.

---

## ✅ Best Practices Followed

- Uses `log()` instead of banned file operations
- In-game messages are debug-friendly via `game.print()`
- Global table usage (`global.ai_log`) ensures state persistence
- Compatible with Factorio 2.0.41+

---

## 🛠️ Extending the Mod

You can enhance this mod by adding:

- Commands for manual control (`/ai-start`, `/ai-stop`)
- Configurable settings via `settings.lua`
- UI elements using `mod-gui`
