# ASCII Pacman

ASCII Pacman is a simple implementation of the classic Pacman game using ASCII characters in the C programming language. The game is played in the console window and features the iconic Pacman character, ghosts, and a maze-like game board.

## Features

- Classic Pacman gameplay with ASCII graphics
- Player control using WASD or arrow keys
- Ghosts with AI behavior (chasing, scattering, frightened, and eaten states)
- Power pellets that allow Pacman to eat ghosts temporarily
- Score tracking and high score display
- Sound effects using the Windows Multimedia API (winmm)

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC, Clang, or MSVC)
- Windows operating system (for sound support using winmm)

### Building and Running

1. Clone the repository:

```shell
git clone https://github.com/coding-pelican/pacman-c.git
```

2. Navigate to the project directory:

```shell
cd pacman-c
```

3. Compile the source code:

```shell
clang -o pacman.exe src\\pacman.c src\\audio_winmm.c -lwinmm
```

4. Run the game:

```shell
./pacman.exe
```

## Gameplay

- Use the WASD or arrow keys to control Pacman's movement.
- Eat all the pellets in the maze to clear it.
- Avoid the ghosts, as they will chase Pacman and try to catch him.
- Eat power pellets to temporarily turn the ghosts blue, allowing Pacman to eat them for bonus points.
- The game ends when Pacman loses all his lives or the game is cleared.

## Code Structure

The project consists of the following files:

- `pacman.c`: The main game logic and rendering code.
- `audio.h`: Header file containing audio-related function declarations.
- `audio_winmm.c`: Implementation of audio functions using the Windows Multimedia API.
- `README.md`: This readme file providing an overview of the project.

The code is organized into sections using region tags for better readability and navigation.

## License

This project is released under the MIT License. See the [LICENSE](./LICENSE) file for more details.

## Acknowledgements

- This game is a clone (in progress) based on the original Pac-Man game developed by Namco.

## Contributing

Contributions are welcome! If you find any bugs or have suggestions for improvements, please open an issue or submit a
pull request. (It's a project I work on occasionally, and there are many areas that need refactoring or have potential
bugs.)

## Contact

For any questions or inquiries, please contact the project author:

- Name: Gyeongtae Kim
- Email: <codingpelican@gmail.com>

Enjoy playing ASCII Pacman!
