VARNAME = error
$(VARNAME) += "!"
NAME = 
SRCS = ./main.c ./ft_strlen.c ./number.dict
OBJ = $(SRCS:%.C=%.O)
	CFLAGS += -WAall

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ)
	./$(NAME)
	@echo "it worked!"
	$(shell ls)
%.o: %.c
	gcc $(CFLAGS) -c -o $@ $^
