/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:58:13 by slayer            #+#    #+#             */
/*   Updated: 2026/04/01 22:25:44 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/miniShell_exec.h"

int	apply_redirects(t_redir *redir)
{
	int fd;

	while (redir)
	{
		if (redir->type == R_IN)          // <
		{
			fd = open(redir->file, O_RDONLY);
			if (fd == -1) { perror(redir->file); return -1; }
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == R_OUT)    // >
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1) { perror(redir->file); return -1; }
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == R_APPEND) // >>
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1) { perror(redir->file); return -1; }
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	/*         else if (redir->type == R_HEREDOC) // <<
		{
			dup2(redir->heredoc_fd, STDIN_FILENO); // fd já preparado no parse
			close(redir->heredoc_fd);
		} */
		redir = redir->next;
	}
	return 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_token		*tokens;
	char		*line;

	(void)argc;
	(void)argv;
	shell.env = NULL;
	shell.cmds = NULL;
	shell.exit_status = 0;
	save_env(&shell.env, envp);
	setup_signals();
	while (1)
	{
		line = readline("prompt> ");
		if (line == NULL)
			return (write(STDOUT_FILENO, "\n", 1), rl_clear_history(), free_env(shell.env), 0);
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		tokens = ft_tokenization_handler(line);
		free(line);
		if (!tokens)
			continue ;
		shell.cmds = ft_parse(tokens);
		ft_clear_token_list(&tokens);
		if (!shell.cmds)
			continue ;
		ft_expand(&shell);
		execute_pipeline(&shell);
			/* return (rl_clear_history(), free_env(shell.env), ft_free_cmd_list(&shell.cmds), shell.exit_status); */
		ft_free_cmd_list(&shell.cmds);
	}
	return (shell.exit_status);
}
