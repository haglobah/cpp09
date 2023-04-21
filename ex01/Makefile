
NAME := RPN

SRC := $(wildcard *.cpp)
HEADS := $(wildcard *.hpp)

CPPFLAGS := -std=c++98 -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(SRC) $(HEADS) Makefile
	c++ $(CPPFLAGS) $(SRC) -o $(NAME)

run :
	$(MAKE) all
	./$(NAME) "1 1 +"

test :
	$(MAKE) all
	./$(NAME) "1 1 -"
	./$(NAME) "2 4 * 8 +"
	./$(NAME) "2 4 8 + *"
	./$(NAME) "2 5 * 4 + 3 2 * 1 + /"
	./$(NAME) "3 2 * 1 -"

	./$(NAME) "1"
	./$(NAME) "a b"
	./$(NAME) "(1 + 2)"

add :
	git add $(SRC) $(HEADS) Makefile