# 🧠 Factorio AI Bot – C++ Version History & Known Fixes

### 🧠 Version 0.1
- Basic log file reader
- Extracted player position from `factorio_ai_data.txt`
- ✅ Functional and stable

---

### 🧠 Version 0.2
- Switched log source to `factorio-current.log`
- Still parsed only player position
- ✅ Stable with updated log path

---

### 🧠 Version 0.3
- Updated regex to match new log format
- 🐞 **Issue:** Did not yet include resource tracking
- ✅ Still stable, preparing for expansion

---

### 🧠 Version 0.4
- Added fallback to read from **both** `factorio-current.log` and `factorio_ai_data.txt`
- 🐞 Bug: resource data was not yet parsed or utilized
- ✅ Compatible with evolving mod outputs

---

### 🧠 Version 0.5
- Added parsing of `[AI Data Chunk]` for resource info
- Extracted and ranked resources
- 🐞 Known Issue: No movement simulation implemented yet
- ✅ Resource logic works, pending next feature

---

### 🧠 Version 0.6
- ✅ Implemented resource prioritization (coal > iron > copper > stone)
- ✅ Selected nearest high-priority resource
- 🕹️ Simulated movement with:
  - `SendInput()`
  - `PostMessage()`
  - `AttachThreadInput()` (all failed in Factorio)
- ⚠️ **Major Finding:** Factorio blocks simulated input
- ❌ None of the methods could move the player
- 🔄 Next step: explore external input injection tools (e.g., vJoy, Interception)

---

### 🧠 Version 0.7
- ✅ Fixed movement using scan code-based `SendInput` (moves player in-game!)
- ✅ Added player distance checks before moving
- ✅ Enabled diagonal WASD movement
- ✅ Added `mineAtPosition()` to simulate left-click mining when near a resource
- ✅ Introduced adjustable movement step size

---

### 🧠 Version 0.8
- 🧠 Introduced GDI+ screenshot capture for Factorio window
- 🖥️ Replaced `BitBlt` with `PrintWindow`, then full virtual desktop capture using `GetDC(NULL)`
- 📸 Screenshot now covers all monitors
- 🔍 Integrated OpenCV 4.11.0
- 🔁 Scans up to 64 `coal_template_X.png` variations
- ✅ Draws bounding box on best match and saves to `match_debug.png`
- 🚦 Confidence thresholds (0.3 min template, 0.5 final match)
- 🐌 Optimization added to speed up matching

---

## 🔧 Known Fixes Across Versions

- `game.read_file()` crash in mod v0.3.6 → Removed in v0.3.8
- `info.json` not found in some zipped mods → Updated extractor to handle nested folders
- Broken `pressKey()` in v0.6 → Rewritten to use scan codes and corrected syntax
- `PostMessage` not effective → Replaced with `AttachThreadInput` combo
- `pressKey()` redefinition and syntax issues → Cleaned and compiled successfully
- Factorio window screenshot captured black → fixed with full desktop GDI+ capture