# so\_long

## Introduction

This project is a small 2D maze game about Verve: a little grauwling (greyling) who, despite their drab origins, really likes colour. It uses the [`MLX42`](https://github.com/codam-coding-college/MLX42) graphics library (a Codam-developed derivative of the earlier MiniLibX library).

### Compiling

Make sure to also fetch the `libft`, `libftprintf` and `MLX42` submodules. Having done that, the game can be compiled by invoking `make` in the repository's root. Do note that `MLX42` has a number of dependencies of its own: you'd be wise to refer to its documentation to verify if you have all of them.

### Project overview

#### Mandatory features

The project only allows the use of the following libc functions: `open`, `close`, `read`, `write`, `malloc`, `free`, `perror`, `strerror`, `exit`, as well as all functions in the `math` library.

#### Bonus features

The game sports a few nifty sprite animations. This niftiness is however offset by the added presence of evil grauwlingen, who will try to stop Verve from achieving their goals.

## How to play

The game is started by executing the following command in your terminal: `./so_long <path_to_map>`
```
./so_long ./assets/maps/level0.ber
```
Your objective is to collect every rainbow orb on the map and then make your way to the exit.  
A number of premade maps are enclosed in this repository (in the `./assets/maps` subdirectory); you could, however, build a map of your own.

### Map format

The game will only load a map which conforms to the following specifications:
1. The data is stored in a file with a `.ber` extension.
2. The data is formatted in lines of ASCII characters, which every line corresponding to a row of objects and every character signifying a particular object type. If the map contains any other character other than the following, it will be rendered invalid.
	- `0`: empty space;
	- `1`: wall;
	- `P`: player start;
	- `E`: exit;
	- `C`: collectible;
	- `H`: [BONUS] horizontally moving enemy;
	- `V`: [BONUS] vertically moving enemy;
	- `W`: [BONUS] wall-hugging enemy.
3. The map is rectangular in shape and enclosed by wall objects (`1`) around the edges.
4. The map contains exactly one player start (`P`), exactly one exit (`E`) and at least one collectible (`C`).
5. There should be a traversable path from the starting position to the exit. For this purpose, empty space, collectibles and enemy objects count as traversable space.

### Controls

Verve is controlled using the WASD keys.
