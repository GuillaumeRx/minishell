/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 02:52:02 by guroux            #+#    #+#             */
/*   Updated: 2019/07/18 20:05:34 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *modarg(char *arg, char **path)
{
	char	*tmp;
	char	*pmt;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		pmt = ft_strjoin(tmp, arg);
		ft_strdel(&tmp);
		if (access(pmt, X_OK) == 0)
		{
			ft_strdel(&arg);
			deltab(path);
			return (pmt);
		}
		ft_strdel(&pmt);
		++i;
	}
	deltab(path);
	return (arg);
}

char *ft_getenv(char *arg, char ***env)
{
	char	**path;
	int		i;

	i = 0;
	while (env[0][i])
	{
		if (ft_strncmp(env[0][i], "PATH=", 5) == 0)
		{
			path = ft_strsplit(ft_strchr(env[0][i], '=') + 1, ':');
			return (modarg(arg, path));
		}
		++i;
	}
	ft_putstr("bash: ");
	ft_putstr(arg);
	ft_putendl(": No such file or directory");
	return (NULL);
}

char	*repvar(char *arg, char ***env)
{
	char	**tmp;
	char 	*var;
	int		i;

	i = 0;
	if (arg[0] == '~')
	{
		while (env[0][i])
		{
			if (ft_strncmp("HOME", env[0][i], ft_strlen("HOME")) == 0)
			{
				tmp = ft_strsplit(env[0][i], '=');
				ft_strdel(&arg);
				ft_strdel(&tmp[0]);
				var = tmp[1];
				free(tmp);
				return(var);
			}
			++i;
		}
		return (NULL);
	}
	if (arg[0] == '$')
	{
		while (env[0][i])
		{
			if (ft_strncmp((arg + 1), env[0][i], ft_strlen(arg) - 1) == 0)
			{
				tmp = ft_strsplit(env[0][i], '=');
				ft_strdel(&arg);
				ft_strdel(&tmp[0]);
				var = tmp[1];
				free(tmp);
				return(var);
			}
			++i;
		}
		return (NULL);
	}
	return (arg);
}

static int	launch(char **args, char ***env)
{
	pid_t	pid;

	if(!(args[0] = ft_getenv(args[0], env)))
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, *env) < 0)
		{
				ft_putstr("minishell: Unknown command ");
				ft_putendl(args[0]);
				return (1);
		}
	}
	else
		wait(&pid);
	return (1);
}

int			execute(char **args, char ***env)
{
	char	*bltins_str[] = {"echo", "exit", "env", "cd", "setenv", "unsetenv", NULL};
	int		(*bltins[])(char **args, char ***env) = {&ft_echo, &ft_exit, &ft_env, &ft_cd, &ft_setenv, &ft_unsetenv, NULL};
	int		i;

	i = 1;
	if (!args[0])
		return (1);
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
