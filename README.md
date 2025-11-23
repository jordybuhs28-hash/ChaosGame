# ChaosGame

##  Requirements Checklist
** SFML Text + Font** used for instructions (`sf::Text`, `sf::Font`)
** Mouse input**: left‑click to place vertices, right‑click to set starting point
** Chaos Game algorithm** implemented with vectors
** Points drawn** using SFML shapes (`sf::CircleShape`)
** Fractal drawn correctly** with convergence rules
** Runs on Linux** (tested build)

##  Extra Credit Features
** Extended to polygons with 3–10 sides (triangle to  decagon)
** Correct ratios applied:
  * Triangle: `0.5`
  * Square: `0.5`
  * Pentagon: `1/φ ≈ 0.618`
  * Hexagon: `2/3 ≈ 0.667`
  * Heptagon: `0.692`
  * Octagon: `0.707`
  * Nonagon: `0.742`
  * Decagon: `0.764`
**Prevents repeating the same vertex twice in a row (for polygons ≥4 sides)

## Enhancements Beyond Requirements
** Polygon outline preview (yellow lines connecting vertices in click order)
** Restart (`R`) and quit (`Esc`) controls
** Completion notification: *“Fractal complete! Press R to restart or Esc to quit.”*
** Shape‑based fractal colors:
** Triangle to Green
** Square to Blue
  * Pentagon to Magenta
  * Hexagon to Cyan
  * Heptagon to Yellow
  * Octagon to Orange
  * Nonagon to Red
  * Decagon to White
** Legend text showing polygon name and sides (e.g., *“Pentagon fractal (5 sides)”*)
** Larger red dots for vertices, smaller colored dots for fractal points-

## Build & Run Instructions

### Linux
```bash
# Install SFML (example for Ubuntu/Debian)
sudo apt-get install libsfml-dev

# Clone repo
git clone https://github.com/jordybuhs28-hash/ChaosGame.git
cd ChaosGame

# Build
make

# Run
make run
