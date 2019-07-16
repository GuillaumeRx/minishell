/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 02:52:02 by guroux            #+#    #+#             */
/*   Updated: 2019/07/16 19:37:17 by guroux           ###   ########.fr       */
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

char	*repvar(char *arg, char **env)
{
	char **tmp;
	if (arg[0] == '~')
	{
		while (*env)
		{
			if (ft_strncmp("HOME", *env, ft_strlen("HOME")) == 0)
			{
				tmp = ft_strsplit(*env, '=');
				return(tmp[1]);
			}
			++env;
		}
	}
	if (arg[0] == '$')
	{
		while (*env)
		{
			if (ft_strncmp((arg + 1), *env, ft_strlen(arg) - 1) == 0)
			{
				tmp = ft_strsplit(*env, '=');
				return(tmp[1]);
			}
			++env;
		}
		return (NULL);
	}
	return (arg);
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
	char	*bltins_str[] = {"echo", "exit", "env", "cd", "setenv", NULL};
	int		(*bltins[])(char **args, char **env) = {&ft_echo, &ft_exit, &ft_env, &ft_cd, &ft_setenv, NULL};
	int		i;

	i = 1;
	if (!args[0])
		return 1;
	while (args[i] != NULL)
	{
		args[i] = repvar(args[i], env);
		++i;
	}
	i = 0;
	while (bltins_str[i] != NULL)
	{
		if (ft_strcmp(args[0], bltins_str[i]) == 0)
			return (*bltins[i])(args, env);
		++i;
	}
	return (launch(args, env));
}
