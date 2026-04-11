/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:13 by slayer            #+#    #+#             */
/*   Updated: 2026/04/11 19:56:10 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

static void	shell_init(t_shell *shell, char **envp)
{
	shell->env = NULL;
	shell->cmds = NULL;
	shell->exit_status = 0;
	shell->is_subshell = 0;
	shell->saved_in = -1;
	shell->saved_out = -1;
	save_env(&shell->env, envp);
	setup_signals();
}

static void	handle_eof(t_shell *shell)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_clear_history();
	free_env(shell->env);
}

static void	process_line(t_shell *shell, char *line)
{
	t_token	*tokens;

	add_history(line);
	tokens = ft_tokenization_handler(line);
	free(line);
	if (!tokens)
		return ;
	shell->cmds = ft_parse(tokens);
	ft_clear_token_list(&tokens);
	if (!shell->cmds)
		return ;
	shell->cmds_head = shell->cmds;
	if (ft_expand(shell) == -1)
		return (update_exit_status(shell, 1), ft_free_cmd_list(&shell->cmds_head));
	if (ft_setup_heredocs(shell->cmds) == -1)
		return (ft_free_cmd_list(&shell->cmds_head));
	execute_pipeline(shell);
	ft_free_cmd_list(&shell->cmds_head);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;
	char	*prompt;

	(void)argc;
	(void)argv;
	shell_init(&shell, envp);
	print_banner();
	while (1)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line)
			return (handle_eof(&shell), shell.exit_status);
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		process_line(&shell, line);
	}
	return (shell.exit_status);
}
