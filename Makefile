CFLAGS = -Wall -Wextra -g
LIB = `sdl2-config --cflags --libs`

all:
	@gcc $(CFLAGS) -o iv iv.c $(LIB)
clean:
	rm iv
