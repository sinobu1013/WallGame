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
CFLAGS = -ltcl86 -ltk86 -g -O3
CC = gcc

$(NAME): $(OBJS)
	$(CC) -g -o $(NAME) $(OBJS) $(CFLAGS)

%.o: %.c %.h
	$(CC) -c -g -O3 -o $*.o $<


all: clean $(NAME) exe

gui: all $(NAME) exeGui

exe:
	game

debug: clean $(NAME)

exeGui:
	game gui

clean:
	rm -f $(NAME) $(OBJS)