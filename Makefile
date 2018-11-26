CC=gcc
CFLAGS=-Wall -std=c99

all: filesplit

timed: CFLAGS=-Wall -std=c99 -DTIMEPROG
timed: filesplit
