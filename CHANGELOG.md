# Changelog

## v0.8
- Added full screen screenshot capture using GDI (multi-monitor support)
- Integrated OpenCV template matching with coal sprite sheet tiles
- Loops through 64 coal template variations for detection
- Draws red rectangle on best match in match_debug.png
- Thresholds optimized for testing (`maxVal > 0.3`, final match > 0.5)

## v0.7
- Movement refined to include diagonal keypress logic
- Added mining logic using mouse position + left click
- Added proximity checks before moving or mining
- Updated logging and AI scoring system

## v0.6
- Initial working version
- Reads player and resource data from Factorio logs
- Moves toward highest scoring resource
- Simulates WASD keypresses using SendInput