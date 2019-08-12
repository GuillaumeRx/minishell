/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:03:36 by guroux            #+#    #+#             */
/*   Updated: 2019/08/12 18:54:17 by guroux           ###   ########.fr       */
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
				*env = remenv(i, *env);
				return (1);
			}
			++i;
		}
	}
	return (0);
}

int		ft_exit(char **args, char ***env)
{
	(void)env;
	(void)args;
	return (0);
}
