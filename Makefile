NAME = game
SRC = main.c
SRCDIR = .
MAIN_FILE = src/c/
GAME_FILE = src/c/game/
PROG_FILE = src/c/prog/
SRCS = ${wildcard $(SRCDIR)/$(MAIN_FILE)*.c $(SRCDIR)/$(GAME_FILE)*.c $(SRCDIR)/$(PROG_FILE)*.c}
OBJS = $(SRCS:.c=.o)
CC = gcc

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

%.o: %.c %.h
	$(CC) -c -o $*.o $<

all: clean $(NAME) exe

exe:
	game

clean:
	rm -f $(NAME) $(OBJS)