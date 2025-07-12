# Text-Based RPG Game

## Introduction

In this project, I developed a **text-based RPG** where the player takes on the role of a **warrior** facing various **monsters**, **wild animals**, and **extreme environments** with different room systems. The game incorporates elements such as **equipment**, **food**, and **drinks**, which enhance the player’s abilities. Players may also be **poisoned** by consuming items or from enemy attacks, adding complexity and engagement to the gameplay.

---

## Implementation Details

### Movement
The movement system is handled by the `Player` and `Room` classes. The `triggerEvent()` function in `Room` works alongside the `handleMovement()` function in `Dungeon`, allowing navigation through directions like **north**, **south**, **east**, and **west**. Each `Room` object holds references to its neighbors, creating a dynamic and responsive exploration system.

### Showing Status
Real-time player stats are shown using the `triggerEvent()` function in `Player`. This includes:
- Name
- Health
- Attack & Defense
- Dodge Chance
- Gold
- Buffs & Debuffs
- Equipped Items
- Inventory
- Hunger, Thirst, Poison status

These updates help players make informed decisions during the game.

### Pick Up Items
Item interactions are managed by the `Item` class. Players can:
- Pick up, store, equip, and unequip items
- Boost stats or heal
- Use `equipItem()` and `unequipItem()` in `Player`

This system adds tactical depth and affects gameplay significantly.

### Fighting System
Combat occurs via the `triggerEvent()` method in the `Monster` and `Animal` classes. Players can:
- Attack
- Use items
- Retreat  
Combat continues until a winner is decided. Victories may reward players with **gold** or **meat**.

### NPC Interaction
NPCs are handled by the `triggerEvent()` function in the `NPC` class. Players can:
- Trade items
- Gain story-related information  
Each NPC is randomly generated for diversity in gameplay.

### Game Logic
Game progression (win/lose conditions) is tracked across `Dungeon`, `Player`, and other classes. The system:
- Monitors health
- Handles boss fights
- Updates game state

### Hunger System
The `Player` class tracks:
- **Hunger**
- **Thirst**
- **Poison**  

These factors impact health and combat. Players must manage them using `eat()`, `drink()`, and `detoxify()` functions.

### Room System
Rooms are categorized (e.g., **Desert**, **Forest**, **Swamp**), each with unique effects:
- Poison from water
- Terrain hazards  
Players must plan navigation and resources strategically.

### Record System
The `Record` class allows:
- **Saving** with `saveToFile()`
- **Loading** with `loadFromFile()`  
This ensures continuity and enhances user experience.

---

## Class Structure and Functionality

### `Object`
- Base class with `name`, `tag`
- Includes virtual functions `triggerEvent()` and `showStatus()`

### `Item`
- Inherits from `Object`
- Boosts player stats or provides resources

### `GameCharacter`
- Inherits from `Object`
- Base for `Player`, `NPC`, `Monster`, and `Animal`

### `Player`
- Extends `GameCharacter`
- Manages status, combat, inventory, hunger/thirst/poison

### `NPC`
- Extends `GameCharacter`
- Random attributes and trading system

### `Monster`
- Extends `GameCharacter`
- Random attributes, manages combat behavior

### `Animal`
- Extends `GameCharacter`
- Random types, available in `Forest`, `Swamp`, and `Normal` rooms
- Can be food sources or enemies

### `Room`
- Inherits from `Object`
- Handles movement and environmental effects

### `Dungeon`
- Manages game flow and room generation (linear or 2D grid)

### `Record`
- Saves and loads game state
