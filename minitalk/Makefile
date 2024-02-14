CLIENT_NAME = client
SERVER_NAME = server

LIBFT = libft/libft.a
FT_PRINTF = ft_printf/ft_printf.a

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror

CLIENT_SRC = client.c
SERVER_SRC = server.c

CLIENT_OBJ = client.o
SERVER_OBJ = server.o

all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME):
	$(MAKE) all -C libft
	$(MAKE) all -C ft_printf
	$(CC) $(CC_FLAGS) $(CLIENT_SRC) $(LIBFT) $(FT_PRINTF) -o $(CLIENT_NAME)

$(SERVER_NAME):
	$(CC) $(CC_FLAGS) $(SERVER_SRC) $(LIBFT) $(FT_PRINTF) -o $(SERVER_NAME)

clean:
	rm -rf $(CLIENT_OBJ)
	rm -rf $(SERVER_OBJ)
	$(MAKE) clean -C libft
	$(MAKE) clean -C ft_printf

fclean: clean
	rm -f $(CLIENT_NAME)
	rm -f $(SERVER_NAME)
	$(MAKE) fclean -C libft
	$(MAKE) fclean -C ft_printf

re: fclean all
