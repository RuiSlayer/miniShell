NAME = miniShell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = main_exec.c echo.c pwd.c env.c save_env.c cd.c update_env.c export.c unset.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(MAKE) -C 42libft
	$(CC) $(CFLAGS) $(OBJS) -I. 42libft/libft.a -o $(NAME) -lreadline

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