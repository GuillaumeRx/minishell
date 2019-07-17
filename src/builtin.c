/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:12:59 by guroux            #+#    #+#             */
/*   Updated: 2019/07/17 20:58:31 by guroux           ###   ########.fr       */
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

int		ft_exit(char **args, char ***env)
{
	(void)env;
	(void)args;
	return (0);
}

int		ft_env(char **args, char ***env)
{
	int		i;

	(void)args;
	i = 0;
	while(env[0][i] != NULL)
	{
		ft_putendl(env[0][i]);
		++i;
	}
	return (1);
}

int		ft_setenv(char **args, char ***env)
{
	int i;
	char *tmp;

	i = 0;
	if (tablen(args) != 3)
		return (0);
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

int		ft_cd(char **args, char ***env)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (args[1])
	{
		if (chdir(args[1]) == -1)
			return (0);
	}
	else
	{
		chdir(tmp = repvar("~", env));
		ft_strdel(&tmp);
	}
	while (env[0][i])
	{
		if (ft_strncmp("PWD", env[0][i], ft_strlen("PWD")) == 0)
		{
			ft_strdel(&env[0][i]);
			tmp = getcwd(tmp, 0);
			env[0][i] = ft_strjoin("PWD=", tmp);
			ft_strdel(&tmp);
		}
		++i;
	}
	return (1);
}
