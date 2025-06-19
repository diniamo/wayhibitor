PREFIX := /usr/local
CC ?= cc
CFLAGS := -Wall -Wextra -Wno-unused-parameter -O3

SRCS := main.c idle-inhibit-unstable-v1.c
LIBS := -lwayland-client
TARGET := wayhibitor

build:
	mkdir -p build
	$(CC) $(CFLAGS) -o build/$(TARGET) $(SRCS) $(LIBS)

run: build
	build/$(TARGET)

install:
	install -D build/$(TARGET) $(PREFIX)/bin/$(TARGET)

clean:
	rm -r build

.PHONY: build install clean
