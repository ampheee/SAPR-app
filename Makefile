CFLAGS=-Wall -Wextra
FLAGS=-g
LIBS=gtk+-3.0
INCLUDE=./include/ `pkg-config --cflags --libs $(LIBS)`
SRC=$(shell find . -name '*.c')
BUILD_DIR=build

APP_NAME=SAPR_BAR

.PHONY: all build_bin build_exe64 build exe32 dist test style format coverage install_libyaml clean

all:

build_bin:
	mkdir -p $(BUILD_DIR)
	gcc	-rdynamic $(SRC) $(CFLAGS)	$(FLAGS) -I $(INCLUDE) -o $(BUILD_DIR)/$(APP_NAME)
	./$(BUILD_DIR)/$(APP_NAME)

build_exe32:
	i686-w64-mingw32-gcc	$(SRC) $(CFLAGS)	$(FLAGS) -I $(INCLUDE) -o $(BUILD_DIR)/$(APP_NAME)_32.exe

build_exe64:
	x86_64-w64-mingw32-gcc $(SRC) $(CFLAGS)	$(FLAGS) -I $(INCLUDE) -o $(BUILD_DIR)/$(APP_NAME)_64.exe

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
