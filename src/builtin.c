/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:12:59 by guroux            #+#    #+#             */
/*   Updated: 2019/08/12 18:57:03 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **args, char ***env)
{
	(void)env;
	args++;
	while (*args)
	{
		ft_putstr(*args);
		ft_putchar(' ');
		++args;
	}
	ft_putchar('\n');
	return (1);
}

int		ft_env(char **args, char ***env)
{
	int		i;

	(void)args;
	i = 0;
	while (env[0][i] != NULL)
	{
		ft_putendl(env[0][i]);
		++i;
	}
	return (1);
}

int		ft_setenv(char **args, char ***env)
{
	int		i;
	char	*tmp;

	i = 0;
	if (tablen(args) != 3)
		return (1);
	while (env[0][i] != NULL)
	{
		if (ft_strncmp(args[1], env[0][i], ft_strlen(args[1])) == 0)
		{
			ft_strdel(&env[0][i]);
			tmp = ft_strjoin(args[1], "=");
			env[0][i] = ft_strjoin(tmp, args[2]);
			ft_strdel(&tmp);
			return (1);
		}
		++i;
	}
	tmp = ft_strjoin(args[1], "=");
	*env = realoc_tab(*env, ft_strjoin(tmp, args[2]));
	ft_strdel(&tmp);
	return (1);
}

int		gotodir(char ***env)
{
	char *tmp;

	if (!(tmp = repvar(ft_strdup("~"), env)))
	{
		ft_putendl("HOME not set");
		return (0);
	}
	if (!(chdir(tmp)))
	{
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&tmp);
	return (1);
}

int		ft_cd(char **args, char ***env)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (tablen(args) <= 2)
	{
		if (args[1])
		{
			if (chdir(args[1]) == -1)
			{
				ft_putstr("cd: The directory '");
				ft_putstr(args[1]);
				ft_putendl("' does not exist");
				return (1);
			}
		}
		else
		{
			if (!(gotodir(env)))
				return (1);
		}
		tmp = getcwd(tmp, 0);
		reppwd(env, tmp, i);
	}
	else
	{
		ft_putendl("Too many args for cd command");
		return (1);
	}
	return (1);
}
