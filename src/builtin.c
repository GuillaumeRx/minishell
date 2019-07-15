/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:12:59 by guroux            #+#    #+#             */
/*   Updated: 2019/07/10 15:53:56 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **args, char **env)
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

int		ft_exit(char **args, char **env)
{
	(void)env;
	(void)args;
	return (0);
}

int		ft_env(char **args, char **env)
{
	(void)args;
	while(*env)
	{
		ft_putendl(*env);
		++env;
	}
	return (1);
}

int		ft_setenv(char **args, char **env)
{
	int i;
	char *tmp;

	i = 0;
	if (tablen(args) != 3)
		return (0);
	while (env[i] != NULL)
	{
		if (ft_strncmp(args[1], env[i], ft_strlen(args[0])))
		{
			ft_strdel(&env[i]);
			tmp = ft_strjoin(args[1], "=");
			env[i] = ft_strjoin(tmp, args[2]);
			ft_strdel(&tmp);
			return (1);
		}
		++i;
	}
	tmp = ft_strjoin(args[1], "=");
	env = realoc_tab(env, ft_strjoin(tmp, args[2]));
	ft_strdel(&tmp);
	return (1);
}

int		ft_cd(char **args, char **env)
{
	(void)env;
	if (chdir(args[1]) == -1)
		return (0);
	return (1);
}
