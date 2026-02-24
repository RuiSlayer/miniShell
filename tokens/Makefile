NAME = miniShell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
SRCS = tokens_handler.c tokens_appenders.c tokens_lst.c tokens_utils.c tokens_tester.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C 42libft
	$(CC) $(CFLAGS) $(OBJS) -I. 42libft/libft.a $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C 42libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C 42libft fclean

re: fclean all

.PHONY: all clean fclean re