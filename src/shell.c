/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 02:52:02 by guroux            #+#    #+#             */
/*   Updated: 2019/08/21 19:40:22 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	(*g_bltins[6])(char **args, char ***env) = {
	&ft_echo,
	&ft_exit,
	&ft_env,
	&ft_cd,
	&ft_setenv,
	&ft_unsetenv
};

char		*modarg(char *arg, char **path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		if ((tmp = testpath(arg, path[i])))
		{
			deltab(path);
			return (tmp);
		}
		i++;
	}
	deltab(path);
	ft_putstr("minishell: Unknown command ");
	ft_putendl(arg);
	return (NULL);
}

char		*ft_getenv(char *arg, char ***env)
{
	char	**path;
	int		i;

	i = 0;
	if (access(arg, X_OK) == 0)
		return (arg);
	while (env[0][i])
	{
		if (ft_strncmp(env[0][i], "PATH=", 5) == 0)
		{
			if (!(path = ft_strsplit(ft_strchr(env[0][i], '=') + 1, ':')))
				return (NULL);
			return (modarg(arg, path));
		}
		++i;
	}
	ft_putstr("minishell: ");
	ft_putstr(arg);
	ft_putendl(": No such file or directory");
	return (NULL);
}

static int	launch(char **args, char ***env)
{
	pid_t	pid;
	char	*tmp;

	if (!(tmp = ft_getenv(args[0], env)))
		return (1);
	args[0] = tmp;
	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, *env) < 0)
			return (1);
	}
	else
		wait(&pid);
	return (1);
}

int			execute(char **args, char ***env)
{
	const char	*bltins_str[6] = {
		"echo", "exit", "env", "cd", "setenv", "unsetenv"
	};
	int			i;

	i = 1;
	if (!args[0])
		return (1);
	while (args[i] != NULL)
	{
		args[i] = repvar(args[i], env);
		++i;
	}
	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(args[0], bltins_str[i]) == 0)
			return (*g_bltins[i])(args, env);
		++i;
	}
	return (launch(args, env));
}
