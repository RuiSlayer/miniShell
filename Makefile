NAME = miniShell
CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline -g
SRCS = main.c echo.c pwd.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(MAKE) -C 42libft
	$(CC) $(CFLAGS) $(OBJS) -I. 42libft/libft.a -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C 42libft fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re