# Factorio AI Bot 🤖

An AI bot that reads Factorio logs and simulates player movement using external keyboard input. The project combines a custom Factorio mod with a C++ AI script.

---

## 📦 Project Structure

- **Factorio Mod**: Logs player and resource positions
- **C++ AI Bot**: Reads log files, ranks resources, simulates `WASD` input to move toward high-priority targets

---

## 🔁 AI Logic

1. Read recent lines from `factorio-current.log`
2. Parse:
   - `[AI Player Position]`: Player's current location
   - `[AI Data Chunk]`: Resource name and coordinates
3. Score each resource based on:
   ```
   score = priority / (distance + 1.0)
   ```
4. Select the best-scoring resource
5. Move the player in the best direction using `SendInput` and **scan code injection**

---

## 🧠 Prioritization Logic

```
coal        = 4
iron-ore    = 3
copper-ore  = 2
stone       = 1
```

---

## ✅ Version v0.7 (Latest)

- ✅ Uses scan codes via `SendInput()` to bypass Factorio input blocking
- ✅ Moves in steps of 5 simulated keypresses per direction
- ✅ Calculates and updates distance to target in real-time
- ✅ Scans only the last 500 lines of logs to prevent stale data overload
- ✅ Logs movement and target details to console for debugging

---

## 🗂 Directory Layout

```
factorio-ai-bot/
├── cpp/
│   ├── ai_bot_vv0.6.cpp   # Crude single-tap movement
│   └── ai_bot_vv0.7.cpp   # Repeated movement logic (current)
├── docs/
│   ├── cpp_version_history.md
│   ├── mod_version_history.md
│   └── MOD_STRUCTURE.md
├── Factorio Mod Versions/
│   └── factorio_ai_bot_0.x.x.zip
├── README.md
└── CHANGELOG.md
```

---

## 🔧 Requirements

- Factorio (1.1+)
- Windows OS (due to `SendInput`)
- Run C++ bot **as Administrator**
- Use **windowed** or **borderless** mode for input simulation

---

## 🚀 Roadmap

- [ ] Add diagonal movement (press two keys simultaneously)
- [ ] Implement proximity stop zone
- [ ] Web-based UI dashboard
- [ ] Auto-building infrastructure (miners, belts, etc.)