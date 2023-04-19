
NAME := btc

SRC := $(wildcard *.cpp)
HEADS := $(wildcard *.hpp)

CPPFLAGS := -std=c++98 -Wall -Wextra #-Werror

all : $(NAME)

$(NAME) : $(SRC) $(HEADS) Makefile
	c++ $(CPPFLAGS) $(SRC) -o $(NAME)

run :
	$(MAKE) all
	./$(NAME) "main.cpp"

test : 
	$(MAKE) all
	./$(NAME) "input.txt"
	./$(NAME) "lala"

add :
	git add $(SRC) $(HEADS) Makefile