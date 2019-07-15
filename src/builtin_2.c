/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 16:03:36 by guroux            #+#    #+#             */
/*   Updated: 2019/07/10 16:06:18 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unsetenv(char **args, char **env)
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