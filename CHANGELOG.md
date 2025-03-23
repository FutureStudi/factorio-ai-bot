# 🧾 CHANGELOG

## v0.7
- Added repeated movement (5 key presses per direction)
- Uses scan codes for keyboard injection (SendInput)
- Player position and distances update dynamically
- Filters to recent 500 lines of logs for real-time decision making
- Console debug output for position, resources, and score

## v0.6
- Functional first build with:
  - Resource detection and prioritization
  - Basic movement using single key presses (scan codes)
  - Fallback to `SendInput()` with VK scan codes