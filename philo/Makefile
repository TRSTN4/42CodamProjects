NAME = philo

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror -Iincludes/

SOURCE = \
	src/main.c \
	src/routine.c \
	src/utils.c \

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SOURCE:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
