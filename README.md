This code was written as a final project for OOP classes, at PUT, Automatic Control and Robotics field

## Gameplay

### Modes

1. **Standard Mode**
   - **Objective:** Reach the final target while avoiding or surviving enemy encounters.

2. **Artillery Mode**
   - **Objective:** Reach the final target while avoiding enemy attacks and artillery fire.
   - **Mechanic:** Artillery periodically shoots at the player. Use the umbrella by pressing `Spacebar` to shield against artillery damage.

### Controls

- **Movement:**
  - `W` - forward
  - `S` - backward
  - `A` - left
  - `D` - right
- **Shooting:** mouse right-click 
- **Additional Controls:**
  - `Spacebar`: Stop movement or activate umbrella (Artillery Mode)
  - `Shift`: sprint 

### Bonuses

- **Firecamp:** Regenerate health points 
- **Ammo Packs:**: +20 ammunition

### Enemy Behavior

- Enemies automatically shoot at the player when they have a clear line of sight.

## Map Customization

### Image Specifications

- **Size:** 700 x 700 pixels

### Color Codes for Map Elements

| Object                         | Color Code | Description                                     |
|--------------------------------|------------|-------------------------------------------------|
| **Target**                     | `#0001FE`  | Deep Blue - final destination                   |
| **Firecamp**                   | `#ffff00`  | Yellow - healthpoints regeneration              |
| **Ammo Packs**                 | `#01ff01`  | Bright green - +20 ammo                         | 
| **Walls**                      | `#000000`  | Black - walls                                   |
| **Enemy Trajectories**         | `#01FF01`  | Red - Paths enemies follow                      |

- enemies follow the longest middle line of the rectangle.
- starting point is always at the **left bottom corner** of the map.

### Configuration Files

- **Format:** Each map has a corresponding configuration file
  - **First Line:** Starting ammunition
  - **Second Line:** Initial health points
-Place configuration files in the `config` directory, where each number of config file correspond to map, for example con1 -> map1

### Example Maps

![Map 1](https://github.com/qemc/SFML_2d_game/blob/master/SFML_2d_game/images/maps/map1.png?raw=true)  
*example of raw png map*

![Example PNG](https://github.com/qemc/SFML_2d_game/blob/master/SFML_2d_game/images/png1.PNG)  
*how dos it looks like imported*


## Installation

All files are ready to run with Visual Studio 2022.
