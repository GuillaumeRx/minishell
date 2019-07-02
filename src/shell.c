/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 02:52:02 by guroux            #+#    #+#             */
/*   Updated: 2019/07/02 23:05:04 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *modarg(char *arg, char **path)
{
	char *tmp;
	char *pmt;

	tmp = NULL;
	pmt = NULL;
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		pmt = ft_strjoin(tmp, arg);
		if (access(pmt, X_OK) == 0)
			return (pmt);
		ft_strdel(&tmp);
		ft_strdel(&pmt);
		++path;
	}
	return (NULL);
}

char *ft_getenv(char *arg, char **env)
{
	char **path;

	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			path = ft_strsplit(ft_strchr(*env, '=') + 1, ':');
			return (modarg(arg, path));
		}
		++env;
	}
	return (NULL);
}

static int	launch(char **args, char **env)
{
	pid_t	pid;

	pid = fork();
	args[0] = ft_getenv(args[0], env);
	if (pid == 0)
	{
		if (execve(args[0], args, env) < 0)
				return (0);
	}
	else
		wait(&pid);
	return (1);
}

int			execute(char **args, char **env)
{
	if (!args[0])
		return 1;
	// TODO : check if its a builtin
	return (launch(args, env));
}
