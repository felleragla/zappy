##
## EPITECH PROJECT, 2025
## zapppy
## File description:
## Makefile
##

CC = gcc
CXX = g++

FLAGS = -Wall -Wextra -Werror -std=c++20 -fPIC

GUI_BIN = zappy_gui
SERVER_BIN = zappy_server
IA_BIN = zappy_ai

GUI_SRC = src/gui/Graphical.cpp src/gui/Command.cpp src/gui/main.cpp src/gui/Player.cpp src/gui/Camera.cpp
SERVER_SRC = src/server/main.c src/server/parser.c src/server/server.c\
			src/server/parse_teams.c src/server/maping.c src/server/event.c\
			src/server/commandlist.c src/server/server1.c src/server/parsing.c
#IA_SRC = src/ia/main.cpp src/ia/protocol_parser.cpp src/ia/network.cpp src/ia/command_buffer.cpp src/ia/time_manager.cpp

OBJ_GUI = $(GUI_SRC:.cpp=.o)
OBJ_SERVER = $(SERVER_SRC:.c=.o)
#OBJ_IA = $(IA_SRC:.cpp=.o)

all: zappy_server zappy_gui #zappy_ai

zappy_gui: $(OBJ_GUI)
	$(CXX) -o $(GUI_BIN) $(OBJ_GUI) $(CXXFLAGS) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

zappy_server: $(OBJ_SERVER)
	$(CC) -o $(SERVER_BIN) $(OBJ_SERVER) $(CFLAGS)

# zappy_ai: $(OBJ_IA)
# 	$(CXX) -o $(IA_BIN) $(OBJ_IA) $(CXXFLAGS)

clean:
	rm -f $(OBJ_GUI) $(OBJ_SERVER)

fclean: clean
	rm -f $(GUI_BIN) $(SERVER_BIN) 
	rm -f *.o

re: fclean all