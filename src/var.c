/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 18:45:38 by guroux            #+#    #+#             */
/*   Updated: 2019/08/26 01:37:54 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*expand_var(char *arg, char ***env, int *i)
{
	char	*tmp;
	char	*str;
	int		j;
	int		k;

	j = *i + 1;
	k = 0;
	while ((arg[j] >= 'a' && arg[j] <= 'z')
			|| (arg[j] >= 'A' && arg[j] <= 'Z'))
		j++;
	tmp = ft_strsub(arg, *i + 1, j - *i - 1);
	while (env[0][k] && ft_strncmp(tmp, env[0][k],
			ft_strlen(env[0][k]) - ft_strlen(ft_strchr(env[0][k], '='))) != 0)
		++k;
	str = (env[0][k] != NULL) ? ft_strjoin(env[0][k] + ft_strlen(tmp) + 1,
			arg + j) : ft_strdup(arg + j);
	ft_strdel(&tmp);
	tmp = ft_strsub(arg, 0, *i);
	ft_strdel(&arg);
	arg = ft_strjoin(tmp, str);
	ft_strdel(&str);
	ft_strdel(&tmp);
	return (arg);
}

char			*get_home(char ***env)
{
	char	**tab;
	char	*tmp;
	int		i;

	i = 0;
	while (env[0][i] != NULL)
	{
		if (ft_strncmp("HOME", env[0][i],
			ft_strlen(env[0][i]) - ft_strlen(ft_strchr(env[0][i], '='))) == 0)
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
	ft_putendl("minishell: HOME not set");
	return (NULL);
}

char			*repvar(char *arg, char ***env)
{
	char	*tmp;
	char	*final;
	int		i;

	i = 0;
	if (arg[i] == '~' && (tmp = get_home(env)))
	{
		if (!(final = ft_strjoin(tmp, arg + (i + 1))))
		{
			ft_strdel(&tmp);
			return (NULL);
		}
		ft_strdel(&tmp);
		ft_strdel(&arg);
		return (final);
	}
	while (arg[i] != '\0')
	{
		if (arg[i] == '$')
		{
			arg = expand_var(arg, env, &i);
			i = 0;
		}
		++i;
	}
	return (arg);
}
