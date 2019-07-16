/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:03:36 by guroux            #+#    #+#             */
/*   Updated: 2019/07/17 00:47:48 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unsetenv(char **args, char **env)
{
	int i;
	int idx;

	i = 0;
	idx = 0;
	if (tablen(args) == 2)
	{
		while (env[i] != NULL)
		{
			if (ft_strncmp(args[1], env[i], ft_strlen(args[1])) == 0)
			{
				env = remenv(i, env);
				return (1);
			}
			++i;
		}
	}
	return (0);
}
