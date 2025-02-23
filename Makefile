NAME = game
SRC = main.c
SRCDIR = .
MAIN_FILE = src/c/
GAME_FILE = src/c/game/
PROG_FILE = src/c/prog/
GUI_FILE = src/c/gui/
CPU_FILE = src/c/Strategy/
SRCS = ${wildcard $(SRCDIR)/$(MAIN_FILE)*.c $(SRCDIR)/$(GAME_FILE)*.c $(SRCDIR)/$(PROG_FILE)*.c $(SRCDIR)/$(GUI_FILE)*.c $(SRCDIR)/$(CPU_FILE)*.c}
OBJS = $(SRCS:.c=.o)
CFLAGS = -ltcl86 -ltk86
CC = gcc

$(NAME): $(OBJS)
	$(CC) -O3 -o $(NAME) $(OBJS) $(CFLAGS)

%.o: %.c %.h
	$(CC) -c -O3 -Os -o $*.o $<

all: clean $(NAME) exe

gui: all $(NAME) exeGui

exe:
	game

exeGui:
	game gui

clean:
	rm -f $(NAME) $(OBJS)