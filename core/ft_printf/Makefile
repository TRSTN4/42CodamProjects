NAME = libftprintf.a
LIBFT = libft.a

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror

SRCS = \
		ft_printf.c \
		ft_pf_write.c \
		ft_pf_itop.c \
		ft_pf_itoa.c \
		ft_pf_itoh.c

OBJS = \
		ft_printf.o \
		ft_pf_write.o \
		ft_pf_itop.o \
		ft_pf_itoa.o \
		ft_pf_itoh.o

all: $(NAME)

$(NAME):
	$(CC) $(CC_FLAGS) -c $(SRCS)
	$(MAKE) all -C libft
	cp libft/$(LIBFT) $(NAME)
	ar rc $(NAME) $(OBJS) $(NAME)

clean:
	rm -rf $(OBJS)
	$(MAKE) clean -C libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all
