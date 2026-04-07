/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:27:00 by fgameiro          #+#    #+#             */
/*   Updated: 2026/04/07 17:30:33 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/errors.h"
#include "../42libft/libft.h"
#include "../ft_dprintf/ft_printf.h"
#include <errno.h>

void	ft_syntax_error(char *token)
{
	if (token)
		ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n", token);
	else
		ft_dprintf(2, "minishell: syntax error near unexpected token");
}

/* int	ft_exec(char **argv, char **envp)
{
	char	*path;

	if (ft_strncmp(argv[0], "..", 3) == 0 || ft_strncmp(argv[0], ".", 2) == 0
		|| !**argv)
		return (ft_err_m(false, argv[0], ": command not found\n"), 127);
	if (ft_strchr(argv[0], '/') || ft_strncmp(argv[0], "./", 2) == 0)
		path = ft_strdup(argv[0]);
	else
		path = ft_get_path(argv[0], envp);
	if (!path || access(path, F_OK) != 0)
	{
		if (errno == ENOTDIR)
			return (ft_err_m(true, argv[0], ": Not a directory\n"), 126);
		else if (ft_strchr(argv[0], '/') || ft_strncmp(argv[0], "./", 2) == 0)
			ft_err_m(true, argv[0], ": No such file or directory\n");
		else
			ft_err_m(false, argv[0], ": command not found\n");
		ft_free(&path);
		return (127);
	}
	execve(path, argv, envp);
	if (errno == EACCES)
		return (ft_access_prompt(path, argv[0]), 126);
	ft_err_m(true, argv[0], ": Unexpected execution error\n");
	return (ft_free(&path), 1);
} */
