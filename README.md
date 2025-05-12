# 🪖 Tank Battle

Welcome to **Tank Battle**, a classic console-based strategy game where two tanks engage in combat within a dynamic maze. Move, rotate, and fire — use strategy and precision to eliminate your opponent!

![image](https://github.com/user-attachments/assets/db34b8de-c0db-4fb9-ac5f-07662a23cc95)

---

## 📋 Menu Options

Upon launching the game, the following options are available:

(1) Start a new game
(8) Present instructions and keys
(9) EXIT

---

## 🎮 Controls and Keys

Each player controls their tank by managing the left and right tracks separately. Movement continues in the chosen direction until a wall is hit, a boundary is reached, or the **STAY** key is pressed. Input is case-insensitive.

| Action                | Player 1 | Player 2 |
|----------------------|----------|----------|
| RIGHT track forward  | `E`      | `O`      |
| RIGHT track backward | `D`      | `L`      |
| LEFT track forward   | `Q`      | `U`      |
| LEFT track backward  | `A`      | `J`      |
| STAY (stop moving)   | `S`      | `K`      |
| Shoot                | `W`      | `I`      |

---

## 🔄 Tank Movement Rules

Tanks rotate in place based on which tracks are engaged:

| Keys Used                            | Movement Description                                |
|-------------------------------------|-----------------------------------------------------|
| RIGHT track forward ONLY            | Rotate counter-clockwise (diagonal steps allowed)   |
| RIGHT forward + LEFT backward       | Rotate counter-clockwise (no diagonal)              |
| LEFT track forward ONLY             | Rotate clockwise (diagonal steps allowed)           |
| LEFT forward + RIGHT backward       | Rotate clockwise (no diagonal)                      |

---

## 🧱 Game Elements

| Element                  | Symbol | Notes                                                  |
|--------------------------|--------|--------------------------------------------------------|
| Tank                     | `O`    | Main body of the tank                                  |
| Cannon (UP/DOWN)         | `|`    | Above or below tank body                               |
| Cannon (LEFT/RIGHT)      | `-`    | Left or right of tank body                             |
| Cannon (UP-RIGHT/DOWN-LEFT)| `/` | Diagonal upper-right or lower-left                     |
| Cannon (UP-LEFT/DOWN-RIGHT)| `\` | Diagonal upper-left or lower-right                     |
| Wall                     | `#`    | Static, blocks tank and shell movement                 |
| Mine                     | `@`    | May damage tanks or cause explosions                   |
| Shell (Cannonball)       | `*`    | Fired from cannon, moves in the direction of fire      |

---

## 🕹️ Gameplay Flow

- Tanks begin stationary in a maze.
- Players input movement direction to start continuous motion.
- Players rotate or move tanks to line up cannon shots.
- Firing (`W` / `I`) launches a shell; a cooldown applies.
- Shells explode on contact with tanks, walls, or mines.

---

## 🧠 Features

- Realistic tank rotation using left/right track mechanics.
- 8-directional cannon aiming.
- ASCII-based terminal rendering (compatible with color and monochrome modes).
- Player-vs-player turnless gameplay with real-time motion.

---

## 🛠️ Tech Stack

- **Language:** C++
- **Rendering:** ASCII graphics
- **Architecture:** OOP (`Tank`, `Shell`, `Board`, `Point`, etc.)

---

## 📦 How to Compile

```bash
g++ main.cpp -o TankBattle
./TankBattle
👤 Author
Created by Roy Mar Chaim— 2025

📜 License
This project is licensed under the MIT License.


