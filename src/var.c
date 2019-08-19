/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 18:45:38 by guroux            #+#    #+#             */
/*   Updated: 2019/08/19 19:51:32 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		reptab(char *arg, char **tab, char ***env)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (arg[0] == '$')
		i = 0;
	while (tab[i] != NULL)
	{
		while (env[0][j] != NULL)
		{
			if (ft_strncmp(tab[i], env[0][j],
			ft_strlen(env[0][j]) - ft_strlen(ft_strchr(env[0][j], '='))) == 0)
			{
				tab[i] = replace(tab[i], env, j);
				break ;
			}
			++j;
		}
		if (env[0][j] == NULL)
			return (0);
		j = 0;
		i++;
	}
	return (1);
}

static char		*concat(char **tab, char *final, int i)
{
	char *tmp;

	if (i == 0)
	{
		if (!(tmp = ft_strdup(tab[i])))
		{
			deltab(tab);
			return (NULL);
		}
	}
	else
	{
		if (!(tmp = ft_strjoin(final, tab[i])))
		{
			deltab(tab);
			ft_strdel(&final);
			return (NULL);
		}
		ft_strdel(&final);
	}
	return (tmp);
}

char			*gethome(char ***env)
{
	char	**tab;
	char	*tmp;
	int		i;

	i = 0;
	while (env[0][i])
	{
		if (ft_strncmp("HOME", env[0][i], ft_strlen("HOME")) == 0)
		{
			if (!(tab = ft_strsplit(env[0][i], '=')))
				return (NULL);
			if (!(tmp = ft_strdup(tab[1])))
			{
				deltab(tab);
				return (NULL);
			}
			deltab(tab);
			return (tmp);
		}
		++i;
	}
	return (ft_strdup(""));
}

char			*repvar(char *arg, char ***env)
{
	char	**tab;
	char	*final;
	int		i;

	i = 0;
	if (ft_strcmp(arg, "~") == 0)
		return (gethome(env));
	if (!(tab = ft_strsplit(arg, '$')))
		return (NULL);
	if (!reptab(arg, tab, env))
	{
		ft_strclr(arg);
		return (arg);
	}
	while (tab[i] != NULL)
	{
		if (!(final = concat(tab, final, i)))
		{
			deltab(tab);
			return (NULL);
		}
		++i;
	}
	deltab(tab);
	return (final);
}
