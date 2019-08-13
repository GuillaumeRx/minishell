/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:25:44 by guroux            #+#    #+#             */
/*   Updated: 2019/08/13 19:58:55 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace(char *arg, char ***env, int i)
{
	char **tmp;
	char *var;

	tmp = ft_strsplit(env[0][i], '=');
	ft_strdel(&arg);
	ft_strdel(&tmp[0]);
	var = tmp[1];
	free(tmp);
	return (var);
}

int		repoldpwd(char ***env, char *pwd, int i)
{
	while (env[0][i])
	{
		if (ft_strncmp("OLDPWD", env[0][i], ft_strlen("OLDPWD")) == 0)
		{
			ft_strdel(&env[0][i]);
			env[0][i] = ft_strjoin("OLDPWD=", pwd);
			return (1);
		}
		++i;
	}
	*env = realoc_tab(*env, ft_strjoin("OLDPWD=", pwd));
	return (1);
}

int		reppwd(char ***env, char *pwd, int i)
{
	char	**tab;

	tab = NULL;
	while (env[0][i])
	{
		if (ft_strncmp("PWD", env[0][i], ft_strlen("PWD")) == 0)
		{
			tab = ft_strsplit(env[0][i], '=');
			repoldpwd(env, tab[1], i);
			deltab(tab);
			ft_strdel(&env[0][i]);
			env[0][i] = ft_strjoin("PWD=", pwd);
			ft_strdel(&pwd);
			return (1);
		}
		++i;
	}
	*env = realoc_tab(*env, ft_strjoin("PWD=", pwd));
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
