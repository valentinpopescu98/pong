# pong

A Pong implementation built from scratch in C++ and OpenGL 4.6, with a clean engine/game separation. Two players, local multiplayer, delta-time movement, and angle-based paddle bouncing.

---

## Architecture

The project is split into three layers:

```
engine/     — Core engine: window, render loop, delta time, input, collision base
game/       — Pong-specific logic: ball movement, paddle input, collision, scoring
model/      — OpenGL primitives: VAO, VBO, EBO, Mesh, Shader
```

### Engine layer
- GLFW window with configurable resolution, fullscreen, and VSync
- Main loop: `beforeUpdate` → `update` → `afterUpdate` (clear, render, swap buffers, poll events)
- Delta time computed per frame for framerate-independent movement

### Game layer
- **BallController** — moves ball by `speed * direction * deltaTime`, bounces off walls and paddles
- **PongCollisionManager** — circle vs AABB collision with overlap error tolerance to handle tunneling at high speeds
- **PlayerInputManager** — keyboard input for both players
- **GameEventManager** — detects scoring (ball passes paddle X boundary), resets world, tracks score

### Bounce physics

Wall bounce: Y direction flips.

Paddle bounce: angle is derived from where the ball hits the paddle — normalized hit position on the paddle maps to the Y component of the new direction vector:

```cpp
float normalizedPos = (ball->position.y - paddle->position.y) / (paddleMaxY - paddle->position.y);
ballDirection = glm::vec3(±1, normalizedPos, 0);
```

Hitting the edge sends the ball at a steep angle; hitting the center sends it straight.

Ball glitch correction: if the ball tunnels through a wall between frames, position is snapped back to `wall_center + wall_radius + ball_radius + epsilon`.

Random initial direction: Mersenne Twister (`std::mt19937`) with random X sign (±1) and random Y float in (-1, 1).

---

## Tech Stack

| Layer | Technology |
|---|---|
| Language | C++17 |
| Graphics API | OpenGL 4.6 |
| Windowing | GLFW3 |
| GL Loader | GLAD |
| Math | GLM |

---

## Build

```bash
# Link against OpenGL, GLFW, and GLAD
g++ src/*.cpp src/engine/*.cpp src/game/*.cpp src/model/*.cpp -o pong -lglfw -lGL -ldl
```

Resolution, fullscreen, and VSync are configured in `main.cpp`:

```cpp
Engine* engine = new Engine(800, 600, false, true); // resX, resY, fullscreen, vsync
```

---

## Controls

| Player | Up | Down |
|---|---|---|
| Player 1 (left) | W | S |
| Player 2 (right) | ↑ | ↓ |
