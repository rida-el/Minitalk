NAME1 = server client

NAME2 = server_bonus client_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIB = minitalk.h

LIBS = minitalk_bonus.h

all: $(NAME1)

bonus : $(NAME2)

server_bonus: $(LIBS) server_bonus.o minitalk_utils_bn.o
	$(CC) $(CFLAGS) server_bonus.o minitalk_utils_bn.o -o $@

client_bonus: $(LIBS) client_bonus.o minitalk_utils_bn.o
	$(CC) $(CFLAGS) client_bonus.o minitalk_utils_bn.o -o $@

server: $(LIB) server.o minitalk_utils.o
	$(CC) $(CFLAGS) server.o minitalk_utils.o -o $@

client: $(LIB) client.o minitalk_utils.o
	$(CC) $(CFLAGS) client.o minitalk_utils.o  -o $@

%.o:%.c $(LIB) $(LIBS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf  server_bonus.o server.o client_bonus.o client.o minitalk_utils_bn.o minitalk_utils.o

fclean: clean
	rm -rf client client_bonus server server_bonus

re: fclean all