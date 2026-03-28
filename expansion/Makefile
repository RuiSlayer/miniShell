NAME = expansion.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = expansion.c expansion_quotes.c expansion_utils.c expansion_var.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I.. -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re