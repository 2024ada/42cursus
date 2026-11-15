*This project has been created as part of the 42 curriculum by ucho, nalee.*

# cub3D

![cub3D gameplay screenshot](https://raw.githubusercontent.com/2nani2/assets/main/4circle/cub3D/asset/readme.png)

## Description

cub3D is a first-person 3D maze renderer inspired by early raycasting games such
as Wolfenstein 3D. The program reads a `.cub` map file, validates its textures,
colors, and map, then renders the inside of the maze from the player's point of
view with MiniLibX.

The mandatory part focuses on the core raycasting engine:

- parsing a scene description file with the `.cub` extension
- loading north, south, west, and east wall textures
- applying separate floor and ceiling colors
- validating that the map is surrounded by walls
- placing exactly one player start position (`N`, `S`, `E`, or `W`)
- rendering a smooth interactive window
- moving with `W`, `A`, `S`, and `D`
- rotating with the left and right arrow keys
- exiting cleanly with `ESC` or the window close button

If the scene file is invalid, the program exits cleanly and prints `Error`
followed by an explicit message.

## Instructions

### Requirements

This project is written in C and uses MiniLibX on Linux. If needed, install the
typical X11 development dependencies:

```sh
sudo apt install build-essential libx11-dev libxext-dev libbsd-dev
```

### Compilation

Build the mandatory version:

```sh
make
```

Build the bonus version:

```sh
make bonus
```

Clean object files:

```sh
make clean
```

Remove generated files:

```sh
make fclean
```

Rebuild:

```sh
make re
```

### Execution

Run the program with a `.cub` map file:

```sh
./cub3D maps/mandatory.cub
```

For the bonus version, up to 10 map files can be provided as rounds:

```sh
./cub3D maps/bonus.cub maps/bonus2.cub
```

## .cub File Format

The mandatory `.cub` file contains texture paths, floor and ceiling colors, and
the map. The map must be the last part of the file.

Mandatory identifiers:

- `NO`: north wall texture
- `SO`: south wall texture
- `WE`: west wall texture
- `EA`: east wall texture
- `F`: floor color in `R,G,B` format
- `C`: ceiling color in `R,G,B` format

Mandatory map characters:

- `1`: wall
- `0`: empty floor
- `N`, `S`, `E`, `W`: player start position and direction
- spaces: valid map content that must still be handled safely

Example:

```text
NO ../textures/wall_north.xpm
SO ../textures/wall_south.xpm
WE ../textures/wall_west.xpm
EA ../textures/wall_east.xpm
F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

## Bonus

The bonus build extends the mandatory raycaster into a small game inspired by
Vincent van Gogh and his *Sunflowers* painting. The player collects sunflowers,
survives hostile townspeople, finds items, and returns home to complete the round.

Implemented bonus features include:

- wall collision
- minimap rendering
- doors that can open and close
- animated sprites
- mouse rotation
- props, enemies, collectibles, healing items, and gear items
- HUD, intro/outro screens, and round-based game flow

### Bonus Controls

- `Space`: interact with a door or the home tile in front of the player
- `Z`, `X`, `C`: switch or use bonus gear
- `Q`, `E`: decrease or increase horizontal field of view
- `F`, `R`: decrease or increase vertical field of view
- Left mouse drag: rotate the point of view
- The intro screen includes a Rules button that shows the bonus game rules.

### Bonus Map Format

Additional bonus map symbols and metadata are used for doors, props, mobs, item
textures, background textures, HUD assets, player animations, and goal textures.
These extensions are only required for the bonus version.

Bonus map symbols:

- `a` to `z`: doors
- available uppercase letters: props, when defined by matching metadata
- `M`: enemy spawn tile
- `G`: home/goal tile

Bonus metadata identifiers:

- `T`: wall decoration textures
- `Da` to `Dz`: door textures. Each door definition requires 5 `.xpm` paths.
- `G`: home/goal wall texture
- `P`, `P_D`, `P_Aa` to `P_Az`: player hand, damage overlay, and gear animation
  textures
- `H`: HUD textures
- `I_M`, `I_Ha` to `I_Hz`, `I_Aa` to `I_Az`: mission, healing, and gear item
  textures
- `Ma_F`, `Ma_B`, `Ma_L`, `Ma_R`, `Ma_A`, `Ma_D`: enemy animation textures

## Technical Notes

Each frame is rendered in layers:

1. Reset the depth buffer.
2. Draw the ceiling and floor.
3. Cast rays column by column to draw walls and doors.
4. Sort and draw sprites such as mobs, props, and items.
5. Draw hand animation, effects, HUD, minimap, and scene overlays.
6. Scale the internal render image to the window image and display it with MiniLibX.

Random gameplay placement in the bonus part uses a custom `ft_rand()`
implementation based on a simple linear congruential generator.

## Resources

- Lode's Computer Graphics Tutorial: Raycasting  
  https://lodev.org/cgtutor/raycasting.html
- 42Paris MiniLibX Linux repository and man pages  
  https://github.com/42Paris/minilibx-linux
- MiniLibX tutorial from 42 Docs  
  https://harm-smits.github.io/42docs/libs/minilibx
- Linux `rand(3)` manual page, used as a reference for the custom random number
  generator pattern  
  https://man7.org/linux/man-pages/man3/rand.3.html
- 42 cub3D subject and peer review checklist

AI assistance was used as a development support tool for:

- drafting and editing this README
- brainstorming the bonus game concept and gameplay ideas
- creating monster image resources for the bonus version
- suggesting and refining function names
- reviewing parsing, map validation, and gameplay edge cases

The project implementation, debugging decisions, and final code integration were
reviewed and controlled by the project author.
