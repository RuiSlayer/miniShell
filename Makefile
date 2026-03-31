NAME = miniShell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = main_exec.c signal_handle.c
OBJS = $(SRCS:.c=.o)
LIBS = tokens/tokens.a parser/parser.a built_ins/built_ins.a expansion/expansion.a env/env.a executor/executor.a 42libft/libft.a
VALGRIND = valgrind --show-leak-kinds=all --suppressions=readline.supp

$(NAME): $(OBJS)
	$(MAKE) -C 42libft
	$(MAKE) -C tokens
	$(MAKE) -C parser
	$(MAKE) -C env
	$(MAKE) -C expansion
	$(MAKE) -C built_ins
	$(MAKE) -C executor
	$(CC) $(CFLAGS) $(OBJS) -I. $(LIBS) -lreadline -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME) 2>&1 | tee valgrind.log

all: $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C 42libft fclean
	$(MAKE) -C tokens fclean
	$(MAKE) -C parser fclean
	$(MAKE) -C env fclean
	$(MAKE) -C expansion fclean
	$(MAKE) -C executor fclean
	$(MAKE) -C built_ins fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re