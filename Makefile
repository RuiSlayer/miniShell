NAME = miniShell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = main_exec.c signal_handle.c
OBJS = $(SRCS:.c=.o)
LIBS = tokens/tokens.a parser/parser.a built_ins/built_ins.a 42libft/libft.a

$(NAME): $(OBJS)
	$(MAKE) -C 42libft
	$(MAKE) -C tokens
	$(MAKE) -C parser
	$(MAKE) -C built_ins
	$(CC) $(CFLAGS) $(OBJS) -I. $(LIBS) -lreadline -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C 42libft fclean
	$(MAKE) -C tokens fclean
	$(MAKE) -C parser fclean
	$(MAKE) -C built_ins fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re