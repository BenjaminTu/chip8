CC = g++
SRC_DIR = src
LIB_DIR = lib
OBJ_DIR = obj
SDL_DIR = $(LIB_DIR)/SDL
EXE = game
CPPFLAGS = -std=c++11 -Iinclude -I$(SDL_DIR)/include -MMD -MP
CFLAGS = -Wall
SRCS := $(wildcard $(SRC_DIR)/*.cc) main.cc
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LDFLAGS = -L$(SDL_DIR)/lib
LDLIBS = -lmingw32 -lSDL2main -lSDL2

.PHONY: default

default: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $(EXE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(SRCS)  $(CFLAGS) -c $< -o $@
