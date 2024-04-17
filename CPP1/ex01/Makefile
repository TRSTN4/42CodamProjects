NAME = ZombieHorde

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp Zombie.cpp zombieHorde.cpp newZombie.cpp
OBJS = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
