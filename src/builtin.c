/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:12:59 by guroux            #+#    #+#             */
/*   Updated: 2019/08/13 16:51:42 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		modvar(char **args, char ***env, char *tmp, int i)
{
	ft_strdel(&env[0][i]);
	if (!(tmp = ft_strjoin(args[1], "=")))
		return (0);
	if (!(env[0][i] = ft_strjoin(tmp, args[2])))
	{
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&tmp);
	return (1);
}

int		ft_setenv(char **args, char ***env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (tablen(args) != 3)
		return (1);
	while (env[0][i] != NULL)
	{
		if (ft_strncmp(args[1], env[0][i], ft_strlen(args[1])) == 0)
			return (modvar(args, env, tmp, i));
		++i;
	}
	if (!(tmp = ft_strjoin(args[1], "=")))
		return (0);
	if (!(*env = realoc_tab(*env, ft_strjoin(tmp, args[2]))))
	{
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&tmp);
	return (1);
}
