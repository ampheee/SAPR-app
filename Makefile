CC=gcc
CFLAGS=-Wall -Wextra
FLAGS= -Wl,-export-dynamic
LIBS=gtk+-3.0
INCLUDE=./include/ `pkg-config --cflags --libs $(LIBS)`
SRC_DIR=./src
SRC_PREPROCESSOR=$(SRC_DIR)/preprocessor
SRC_PROCESSOR=$(SRC_DIR)/processor
SRC_POSTPROCESSOR=$(SRC_DIR)/postprocessor
SRC=${SRC_DIR}/main.c $(SRC_PREPROCESSOR)/*.c $(SRC_PROCESSOR)/*c $(SRC_POSTPROCESSOR)/*.c
BUILD_DIR=build

APP_NAME=SAPR_BAR

.PHONY: all build_bin build_win dist test style format coverage install_libyaml clean

all:

build_bin:
	mkdir -p $(BUILD_DIR)
	$(CC) $(SRC) $(CFLAGS)	$(FLAGS) -I $(INCLUDE) -o $(BUILD_DIR)/$(APP_NAME)

build_win:

dist:

test:

clean:
	rm -rf $(BUILD_DIR)/*

style:
	clang-format -style=Google -n $(SRC)

format:
	clang-format -style=Google -i $(SRC)

coverage:

install_libyaml:
	sudo apt install libyaml-dev
