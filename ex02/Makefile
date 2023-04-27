
NAME := PmergeMe

SRC := $(wildcard *.cpp)
HEADS := $(wildcard *.hpp)

CPPFLAGS := -std=c++98 -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(SRC) $(HEADS) Makefile
	c++ $(CPPFLAGS) $(SRC) -o $(NAME)

run :
	$(MAKE) all
	./$(NAME) "1"

test :
	$(MAKE) all
	./$(NAME) 1 2 3 2 9 2 7
	./$(NAME) `jot -r 3 1 100 | tr '\n' ' '`
	./$(NAME) `jot -r 10 1 1000 | tr '\n' ' '`
	./$(NAME) `jot -r 300 1 100000 | tr '\n' ' '`
	./$(NAME) `jot -r 3000 1 100000 | tr '\n' ' '`
	./$(NAME) `jot -r 9000 1 100000 | tr '\n' ' '`

add :
	git add $(SRC) $(HEADS) Makefile