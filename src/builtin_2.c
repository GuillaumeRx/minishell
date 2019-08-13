/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:03:36 by guroux            #+#    #+#             */
/*   Updated: 2019/08/13 17:00:49 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unsetenv(char **args, char ***env)
{
	int i;
	int idx;

	i = 0;
	idx = 0;
	if (tablen(args) == 2)
	{
		while (env[0][i] != NULL)
		{
			if (ft_strncmp(args[1], env[0][i], ft_strlen(args[1])) == 0)
			{
				if (!(*env = remenv(i, *env)))
					return (0);
				return (1);
			}
			++i;
		}
	}
	return (1);
}

int		ft_exit(char **args, char ***env)
{
	(void)env;
	(void)args;
	return (0);
}

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
