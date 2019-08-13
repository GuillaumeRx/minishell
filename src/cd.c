/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 16:47:48 by guroux            #+#    #+#             */
/*   Updated: 2019/08/13 16:48:05 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		lauchcd(char **args, char ***env, int i)
{
	char *tmp;

	tmp = NULL;
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
	return (1);
}

int		ft_cd(char **args, char ***env)
{
	int		i;

	i = 0;
	if (tablen(args) <= 2)
		return (lauchcd(args, env, i));
	else
	{
		ft_putendl("Too many args for cd command");
		return (1);
	}
	return (1);
}