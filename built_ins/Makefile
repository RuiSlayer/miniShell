NAME = built_ins.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = cd.c echo.c env.c export.c pwd.c  unset.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re