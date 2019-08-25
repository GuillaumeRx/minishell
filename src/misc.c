/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:25:44 by guroux            #+#    #+#             */
/*   Updated: 2019/08/26 01:17:01 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		repoldpwd(char ***env, char *pwd, int i)
{
	while (env[0][i])
	{
		if (ft_strncmp("OLDPWD", env[0][i], ft_strlen("OLDPWD")) == 0)
		{
			ft_strdel(&env[0][i]);
			if (!(env[0][i] = ft_strjoin("OLDPWD=", pwd)))
				return (0);
			return (1);
		}
		++i;
	}
	if (!(*env = realoc_tab(*env, ft_strjoin("OLDPWD=", pwd))))
		return (0);
	return (1);
}

int		reppwd(char ***env, char *pwd, int i)
{
	char	**tab;

	while (env[0][i])
	{
		if (ft_strncmp("PWD", env[0][i], ft_strlen("PWD")) == 0)
		{
			if (!(tab = ft_strsplit(env[0][i], '=')))
				return (0);
			if (!(repoldpwd(env, tab[1], i)))
			{
				deltab(tab);
				return (0);
			}
			deltab(tab);
			ft_strdel(&env[0][i]);
			env[0][i] = ft_strjoin("PWD=", pwd);
			ft_strdel(&pwd);
			return (1);
		}
		++i;
	}
	if (!(*env = realoc_tab(*env, ft_strjoin("PWD=", pwd))))
		return (0);
	ft_strdel(&pwd);
	return (1);
}

char	*testpath(char *arg, char *path)
{
	char	*tmp;
	char	*pmt;

	if (!(tmp = ft_strjoin(path, "/")))
		return (NULL);
	if (!(pmt = ft_strjoin(tmp, arg)))
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	ft_strdel(&tmp);
	if (access(pmt, X_OK) == 0)
	{
		ft_strdel(&arg);
		return (pmt);
	}
	ft_strdel(&pmt);
	return (NULL);
}
