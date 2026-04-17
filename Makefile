NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
BUILT_INS = built_ins/cd.c built_ins/echo.c built_ins/env.c built_ins/export.c built_ins/pwd.c built_ins/unset.c built_ins/exit.c built_ins/export_utils.c
ENV_UTILS = env_utils/get_env.c env_utils/save_env.c env_utils/update_env.c
ERRORS = errors/errors.c errors/errors_external_cmds.c
EXECUTOR = executor/cmds_runer.c executor/executor_path.c executor/executor_redirs.c executor/pipeline_loop.c executor/pipe_loop_utils.c executor/pipe_loop_utils2.c executor/executor_redirs_utils.c
EXPANSION = expansion/expansion.c expansion/expansion_quotes.c expansion/expansion_utils.c expansion/expansion_var.c expansion/expansion_args.c expansion/expansion_split.c expansion/expansion_args_utils.c
FT_DPRINTF = ft_dprintf/format_delegator.c ft_dprintf/ft_printf.c ft_dprintf/print_char.c ft_dprintf/print_dec_int.c ft_dprintf/print_hex.c ft_dprintf/print_pointer.c ft_dprintf/print_string.c ft_dprintf/print_uint.c
PARSER = parser/parser.c parser/parser_free.c parser/parser_lst.c parser/parser_utils.c
TOKENS = tokens/tokens_handler.c tokens/tokens_appenders.c tokens/tokens_lst.c tokens/tokens_utils.c
GET_NEXT_LINE = ft_get_next_line/get_next_line.c ft_get_next_line/get_next_line_utils.c
MAIN = main/main_exec.c main/signal_handle.c main/prompt.c
SRCS = $(GET_NEXT_LINE) $(BUILT_INS) $(ENV_UTILS) $(ERRORS) $(EXECUTOR) $(EXPANSION) $(FT_DPRINTF) $(PARSER) $(TOKENS) $(MAIN)
OBJS = $(SRCS:.c=.o)
LIBS = 42libft/libft.a
VALGRIND = valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes -s --track-fds=all --suppressions=./readline.supp ./minishell

$(NAME): $(OBJS)
	$(MAKE) -C 42libft
	$(CC) $(CFLAGS) $(OBJS) -I. $(LIBS) -lreadline -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME) 2>&1 | tee valgrind.log

all: $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C 42libft fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re