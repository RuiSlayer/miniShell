/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:13 by slayer            #+#    #+#             */
/*   Updated: 2026/04/07 18:45:07 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/miniShell_exec.h"

static void shell_init(t_shell *shell, char **envp)
{
	shell->env = NULL;
	shell->cmds = NULL;
	shell->exit_status = 0;
	shell->is_subshell = 0;
	save_env(&shell->env, envp);
	setup_signals();
}

static void handle_eof(t_shell *shell)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_clear_history();
	free_env(shell->env);
}

static void process_line(t_shell *shell, char *line)
{
	t_token	*tokens;
	t_cmd	*head_cmds;

	add_history(line);
	tokens = ft_tokenization_handler(line);
	free(line);
	if (!tokens)
		return ;
	shell->cmds = ft_parse(tokens);
	ft_clear_token_list(&tokens);
	if (!shell->cmds)
		return ;
	ft_expand(shell);
	if (ft_setup_heredocs(shell->cmds) == -1 || )
		return(ft_free_cmd_list(&shell->cmds));
	head_cmds = shell->cmds;
	execute_pipeline(shell);
	shell->cmds = head_cmds;
	ft_free_cmd_list(&shell->cmds);
}

int main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;

	(void)argc;
	(void)argv;
	shell_init(&shell, envp);
	while (1)
	{
		line = readline("prompt> ");
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
