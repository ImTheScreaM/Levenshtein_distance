GCC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Iinclude -fPIC

ALL_SRC = $(wildcard src/*.c)
ALL_TEST = $(wildcard tests/*.c)

OUT_NAME = levenshtein.out
OUT_FILE = output

.PHONY: app start docs

app:
	mkdir -p $(OUT_FILE)
	$(GCC) $(ALL_SRC) $(CFLAGS) -o $(OUT_FILE)/$(OUT_NAME)

start: app
	./$(OUT_FILE)/$(OUT_NAME)

docs:
	doxygen docs/Doxyfile
