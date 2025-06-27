# Zappy - Network Game Project

Zappy is a network game where AI clients compete in teams to reach level 8 first by collecting resources and performing incantations.

## Project Structure

```
ZAPPY/
├── include/           
├── src/             
├── resources/       
├── Makefile         
└── README.md        
```

## Components
## GUI Controls

- **WASD / Arrow Keys**: Move camera
- **Mouse Wheel**: Zoom in/out
- **G**: Toggle grid display
- **I**: Toggle player information
- **T**: Toggle team list
- **P**: Toggle player list
- **Left Click**: Select player
- **ESC**: Deselect player

### Server
The game server manages:
- Game world and map
- Player connections and authentication
- Resource distribution
- Game logic and rules
- Communication between AI clients and GUI

### AI Client
AI clients:
- Connect to the server as team members
- Explore the map and collect resources
- Perform actions to level up
- Communicate with other team members

### GUI
The graphical interface:
- Displays the game world in real-time
- Shows players, resources, and incantations
- Provides game statistics and information

## Building the Project

### Prerequisites
- GCC compiler
- Python 3.x
- SFML library (for GUI)
- Make

### Installation

1. Install SFML (Ubuntu/Debian):
```bash
sudo apt-get install libsfml-dev
```

2. Build the project:
```bash
make
```

This will create three binaries:
- `zappy_server` - Game server
- `zappy_ai` - AI client
- `zappy_gui` - Graphical interface

## Usage

### Starting the Server
```bash
./zappy_server -p <port> -x <width> -y <height> -n <team1> <team2> ... -c <clients_nb> -f <freq>
```

Parameters:
- `-p port`: Server port number
- `-x width`: Map width
- `-y height`: Map height
- `-n team1 team2 ...`: Team names
- `-c clients_nb`: Number of authorized clients per team
- `-f freq`: Reciprocal of time unit for execution of actions

Example:
```bash
./zappy_server -p 4242 -x 10 -y 10 -n team1 team2 -c 3 -f 100
```

### Starting the GUI
```bash
./zappy_gui -p <port> -h <hostname>
```

Parameters:
- `-p port`: Server port number
- `-h hostname`: Server hostname (default: localhost)

Example:
```bash
./zappy_gui -p 4242 -h localhost
```

### Starting AI Clients
```bash
python3 zappy_ai.py -p <port> -n <team_name> -h <hostname>
```

Parameters:
- `-p port`: Server port number
- `-n team_name`: Team name
- `-h hostname`: Server hostname (default: localhost)

Example:
```bash
python3 zappy_ai.py -p 4242 -n team1 -h localhost
```

## Game Rules

### Objective
The first team to have 6 players reach level 8 wins the game.

### Resources
There are 7 types of resources:
- **Food**: Required for survival
- **Linemate**: Required for leveling up
- **Deraumere**: Required for leveling up
- **Sibur**: Required for leveling up
- **Mendiane**: Required for leveling up
- **Phiras**: Required for leveling up
- **Thystame**: Required for leveling up

### Leveling Up
To level up, players must:
1. Gather required resources
2. Be at the correct position with the right number of players
3. Perform an incantation

### Level Requirements
| Level | Players | Linemate | Deraumere | Sibur | Mendiane | Phiras | Thystame |
|-------|---------|----------|-----------|-------|----------|--------|-----------|
| 1→2   | 1       | 1        | 0         | 0     | 0        | 0      | 0         |
| 2→3   | 2       | 1        | 1         | 1     | 0        | 0      | 0         |
| 3→4   | 2       | 2        | 0         | 1     | 0        | 2      | 0         |
| 4→5   | 4       | 1        | 1         | 2     | 0        | 1      | 0         |
| 5→6   | 4       | 1        | 2         | 1     | 3        | 0      | 0         |
| 6→7   | 6       | 1        | 2         | 3     | 0        | 1      | 0         |
| 7→8   | 6       | 2        | 2         | 2     | 2        | 2      | 1         |


## AI Commands

The AI client supports the following commands:
- `Forward`: Move forward
- `Right`: Turn right
- `Left`: Turn left
- `Look`: Look around
- `Inventory`: Check inventory
- `Broadcast <text>`: Send message
- `Connect_nbr`: Get number of unused slots
- `Fork`: Create new player slot
- `Eject`: Eject players from current tile
- `Take <object>`: Take object
- `Set <object>`: Drop object
- `Incantation`: Start incantation

## Development

### Code Style
The project follows the Epitech C coding style guide.

### File Structure
- **server/**: C source files for the server
- **ai/**: Python AI client
- **gui/**: C++ source files for the GUI
- **resources/**: Game assets (textures, fonts)

### Contributing
1. Follow the coding style
2. Test your changes
3. Update documentation if needed

## Troubleshooting

### Common Issues

1. **SFML not found**: Install SFML development libraries
2. **Port already in use**: Choose a different port
3. **Connection refused**: Make sure the server is running
4. **Python module not found**: Check Python installation

### Debug Mode
To enable debug output, you can modify the source code to include debug prints.

## License

This project is part of the Epitech curriculum.