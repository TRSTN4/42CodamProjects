NAME = push_swap
LIBFT = libft/libft.a
FT_PRINTF = ft_printf/ft_printf.a

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror
SRCS = \
		srcs/main.c \
		srcs/utilities.c \
		srcs/index.c \
		srcs/radix.c \
		srcs/force_sort.c \
		srcs/push.c \
		srcs/rotate.c \
		srcs/swap.c \

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CC_FLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) -o $(NAME)

$(OBJS_DIR)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) all -C libft

$(FT_PRINTF):
	$(MAKE) all -C ft_printf

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) clean -C libft
	$(MAKE) clean -C ft_printf

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft
	$(MAKE) fclean -C ft_printf

re: fclean all
