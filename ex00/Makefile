NAME = convert
SRCS = \
	main.cpp \
	ScalarConverter.cpp
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++98
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@rm -f ${OBJS}

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all clean re
