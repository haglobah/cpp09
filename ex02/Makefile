
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

add :
	git add $(SRC) $(HEADS) Makefile