NAME1 = server client
NAME2 = server_bonus client_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = minitalk.h
LIB2 = minitalk_bonus.h

all: $(NAME1)

bonus : $(NAME2)

server_bonus: $(LIBS) server_bonus.o
	$(CC) $(CFLAGS) server_bonus.o -o 

client_bonus: $(LIBS) client_bonus.o
	$(CC) $(CFLAGS) client_bonus.o -o 

server: $(LIB) server.o
	$(CC) $(CFLAGS) server.o  -o

client: $(LIB) client.o
	$(CC) $(CFLAGS) client.o  -o

%.o:%.c $(LIB) $(LIBS)
	$(CC) $(CFLAGS) -c $< -o

clean:
	rm -rf  server_bonus.o server.o client_bonus.o client.o

fclean: clean
	rm -rf client client_bonus server server_bonus
	
re: fclean all