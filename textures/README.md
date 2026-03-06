*This project has been created as part of the 42 curriculum by agarcia, adriescr.*

# cub3D — My first RayCaster with miniLibX

## Description

**cub3D** is a 3D first-person perspective maze renderer inspired by *Wolfenstein 3D*, the legendary 1992 FPS developed by Id Software. The goal is to implement a ray-casting engine from scratch in C using the miniLibX graphical library, generating a realistic view of a maze defined in a `.cub` scene file.

The project covers core concepts of computer graphics: ray-casting mathematics, wall rendering with distance-based projection, texture mapping, event-driven window management, and scene file parsing with strict error handling.

### Mandatory features

- Ray-casting engine rendering walls, floor, and ceiling colors.
- Four directional wall textures (North, South, East, West).
- Scene description file parsing (`.cub` format) with full error handling.
- Smooth window management (minimize, switch, close).
- Keyboard controls:
  - `W` `A` `S` `D` — move the player through the maze.
  - `←` `→` — rotate the point of view.
  - `ESC` or clicking the window close button — exits cleanly.

### Bonus features

- **Wall collisions** — the player cannot walk through walls.
- **Minimap system** — real-time overhead minimap rendered on screen.
- **Doors** — doors that can open and close dynamically (`2` on the map).
- **Animated sprites** — enemies with multi-frame animation.
- **Mouse rotation** — rotate the point of view with the mouse.

---

## Instructions

### Requirements

- A C compiler (`cc`) with flags `-Wall -Wextra -Werror`.
- miniLibX (included under `libs/mlx/` or `libs/mlx_linux/` depending on OS).
- `libft` (included under `libs/libft/`).
- GNU Make.
- macOS or Linux.

### Compilation

```bash
# Mandatory part
make

# Bonus part
make bonus

# Clean object files
make clean

# Full clean (removes binaries)
make fclean

# Recompile everything
make re
```

### Execution

```bash
# Mandatory
./cub3D maps/map1.cub

# Bonus
./cub3D_bonus maps/map1.cub
```

The program takes a single argument: a path to a `.cub` scene description file.

### Scene file format (`.cub`)

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

1111111
1000001
10N0001
1111111
```

| Identifier | Meaning                              |
|------------|--------------------------------------|
| `NO`       | Path to north wall texture           |
| `SO`       | Path to south wall texture           |
| `WE`       | Path to west wall texture            |
| `EA`       | Path to east wall texture            |
| `F`        | Floor color `R,G,B` (0–255 each)     |
| `C`        | Ceiling color `R,G,B` (0–255 each)   |

Map characters:
- `0` — empty space
- `1` — wall
- `2` — door *(bonus only)*
- `N`, `S`, `E`, `W` — player start position and orientation

The map must be the **last element** in the file, closed/surrounded by walls on all sides.

### Error handling

On any misconfiguration, the program exits with `Error\n` followed by a descriptive message.

Example invalid maps are provided in the `maps/` directory for testing.

---

## Resources

### Ray-casting references

  **Harm Smits' 42 Documentation**:
  https://harm-smits.github.io/42docs/projects/cub3d
- **miniLibX documentation** — Linux/macOS graphical library used for rendering:
  https://harm-smits.github.io/42docs/libs/minilibx
- **Wolfenstein 3D (original game, playable in browser)**:
  http://users.atw.hu/wolf3d/
- **Wikipedia — Ray casting**:
  https://en.wikipedia.org/wiki/Ray_casting

### AI usage

AI tools (GitHub Copilot) were used during this project in the following limited and verified ways:

- **Documentation and comments**: generating initial drafts of function-level comments that were then reviewed and corrected manually.
- **Debugging assistance**: asking for explanations of specific C behaviour (e.g., pointer arithmetic, undefined behaviour scenarios) to confirm understanding before applying fixes.
- **README drafting**: generating a first draft of this README based on the subject requirements, reviewed and adapted to match the actual project implementation.

All AI-generated content was critically reviewed, tested, and understood before being incorporated. No AI-generated code was committed without full comprehension and peer review.
