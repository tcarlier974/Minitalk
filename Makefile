CC = gcc
CFLAGS = -Wall -Wextra -Werror

all : server client

server : server.c
	$(CC) $(CFLAGS) -o server server.c

client : client.c
	$(CC) $(CFLAGS) -o client client.c

fclean : clean

clean :
	rm -f server client

re : clean all

.PHONY : all clean re fclean