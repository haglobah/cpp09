
NAME := btc

SRC := $(wildcard *.cpp)
HEADS := $(wildcard *.hpp)

CPPFLAGS := -std=c++98 -Wall -Wextra #-Werror

all : $(NAME)

$(NAME) : $(SRC) $(HEADS) Makefile
	c++ $(CPPFLAGS) $(SRC) -o $(NAME)

run :
	$(MAKE) all
	./$(NAME) "input.csv"

test : 
	$(MAKE) all
	./$(NAME) "input.csv"
	./$(NAME) "lala"

add :
	git add $(SRC) $(HEADS) Makefile