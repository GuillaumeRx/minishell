/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:03:36 by guroux            #+#    #+#             */
/*   Updated: 2019/08/21 21:48:14 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unsetenv(char **args, char ***env)
{
	int i;
	int j;
	int idx;

	i = 0;
	j = 1;
	idx = 0;
	if (tablen(args) > 1)
	{
		while (args[j] != NULL)
		{
			while (env[0][i] != NULL)
			{
				if (ft_strncmp(args[j], env[0][i], ft_strlen(args[1])) == 0)
				{
					if (!(*env = remenv(i, *env)))
						return (0);
				}
				++i;
			}
			i = 0;
			j++;
		}
	}
	return (1);
}

int		ft_exit(char **args, char ***env)
{
	(void)env;
	(void)args;
	ft_putendl("exit");
	return (0);
}

int		ft_echo(char **args, char ***env)
{
	(void)env;
	args++;
	while (*args)
	{
		if (ft_strlen(*args) != 0)
		{
			ft_putstr(*args);
			ft_putchar(' ');
		}
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
