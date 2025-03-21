# 📜 Factorio AI Bot – Mod Version History

### 🧩 Version 0.3.3
- Initial release with:
  - Resource scanning
  - Player position tracking
  - Output via `game.write_file()` to `factorio_ai_data.txt`

### 🧩 Version 0.3.4
- Fixed formatting bug in resource logging:
  - Resource names are now quoted properly:
    ```lua
    "[AI Data Chunk]: name=\"iron-ore\", position={x=0.0, y=0.0}"
    ```

### 🧩 Version 0.3.5
- Introduced a `trim_file()` function to limit file size
- Used `io.open()` to manually trim lines in `factorio_ai_data.txt`

### 🧩 Version 0.3.6
- Attempted to use **`game.read_file()`** (not supported in Factorio API)
- **⚠️ Caused crashes** due to invalid API call

### 🧩 Version 0.3.8
- Removed broken `game.read_file()` logic
- Started storing AI log data in memory via `global.ai_log`

### 🧩 Version 0.3.9
- Added `script.on_init()` and `script.on_load()` to safely initialize `global.ai_log`
- Ensured log survives game reloads

### 🧩 Version 0.4.0
- Ensured `global` table exists at all times
- Improved safety and compatibility

### 🧩 Version 0.4.1
- Fully removed `game.write_file()`
- Replaced output with `log(table.concat(...))` to use Factorio’s internal logging system

### 🧩 Version 0.4.2
- Added player debug messages using `game.print(...)`
- AI data now shows in the **in-game console** for real-time feedback

### 🧩 Version 0.4.3 (Current Stable)
- Cleaned up debug string formatting
- Finalized logging pipeline:
  - `log()` → outputs to `factorio-current.log`
  - `game.print()` → in-game console output
- ✅ Fully stable and compliant with Factorio mod API