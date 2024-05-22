NAME = webserv
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98 #-fsanitize=address -g

INCLUDES = -I./include

HEADERS = $(wildcard ./include/**/*.hpp) $(wildcard ./include/*.hpp)

SOURCES = $(wildcard ./src/**/*.cpp) $(wildcard ./src/*.cpp)

OBJECTS = $(patsubst ./src/%.cpp, ./objects/%.o, $(SOURCES))

# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

./objects/%.o: ./src/%.cpp $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) $(INCLUDES) $^ -o $@
	@echo "\n$(NAME): $(GREEN)$(NAME) object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

clean:
	@rm -rf ./objects
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re: fclean all
