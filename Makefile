CC          := gcc
CFLAGS      := -Werror -Wall -Wextra -pedantic -std=c11 -D_XOPEN_SOURCE=500 -Werror=vla
LDFLAGS     := -lrt -lpthread -pthread

BUILD       := ./build
OBJ_DIR     := $(BUILD)/objects
APP_DIR     := $(BUILD)

SRC := ptlab.c counter_unsafe.c counter_mutex.c io_handling.c

TARGET := ptlab

OBJS := $(SRC:%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -MMD -o $@

$(APP_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

-include $(DEPS)

.PHONY: all build clean debug release info test

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CFLAGS += -DDEBUG -g
debug: all

release: CFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

info:
	@echo "[*] Application dir: ${APP_DIR}"
	@echo "[*] Object dir:      ${OBJ_DIR}"
	@echo "[*] Sources:         ${SRC}"
	@echo "[*] Objects:         ${OBJS}"
	@echo "[*] Dependencies:    ${DEPS}"

test: all
	$(APP_DIR)/$(TARGET) counter unsafe 4 100000
	$(APP_DIR)/$(TARGET) counter mutex 4 100000
	$(APP_DIR)/$(TARGET) rwlock 4 2 10000