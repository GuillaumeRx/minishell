/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:12:59 by guroux            #+#    #+#             */
/*   Updated: 2019/07/08 20:00:51 by guroux           ###   ########.fr       */
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
