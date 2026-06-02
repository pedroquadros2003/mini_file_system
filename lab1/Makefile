<<<<<<< HEAD
CC = gcc
CFLAGS = -Wextra -g $(shell pkg-config fuse3 --cflags)
LDLIBS = $(shell pkg-config fuse3 --libs)

BUILD   := ./build
OBJ_DIR := $(BUILD)/objects
APP_DIR := $(BUILD)

TARGET := minifs_ro 

SRC := minifs_ro.c

OBJS := $(SRC:%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

all: build $(APP_DIR)/$(TARGET)

# Compilação dos objetos
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

# Linkagem final
$(APP_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# Inclusão automática das dependências
-include $(DEPS)

.PHONY: all build clean debug release info

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CFLAGS += -DDEBUG -g
debug: all

release: CFLAGS += -O2
release: all

clean:
	-@rm -rf $(BUILD)

info:
	@echo "[*] Application dir: $(APP_DIR)"
	@echo "[*] Object dir:      $(OBJ_DIR)"
	@echo "[*] Sources:         $(SRC)"
	@echo "[*] Objects:         $(OBJS)"
	@echo "[*] Dependencies:    $(DEPS)"
=======
CC          := gcc
#CFLAGS      := -Wall -Wextra -pedantic -g $(shell pkg-config fuse3 --cflags)
CFLAGS      := -Wall `pkg-config fuse3 --cflags --libs` -o minifs_ro

minifs_ro:	minifs_ro.c Makefile
	$(CC) minifs_ro.c -o minifs_ro $(CFLAGS)

mount:		minifs_ro
	mkdir mnt/
	./minifs_ro -f mnt/
>>>>>>> ef6f0dc2b64d65a78fe7804647c5b6f4680544c0
