/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 18:45:38 by guroux            #+#    #+#             */
/*   Updated: 2019/09/02 19:09:39 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*editarg(char *arg, char *str, int i)
{
	char *tmp;

	if (!(tmp = ft_strsub(arg, 0, i)))
	{
		ft_strdel(&str);
		return (NULL);
	}
	ft_strdel(&arg);
	if (!(arg = ft_strjoin(tmp, str)))
	{
		ft_strdel(&tmp);
		ft_strdel(&str);
		return (NULL);
	}
	ft_strdel(&str);
	ft_strdel(&tmp);
	return (arg);
}

char			*expand_var(char *arg, char ***env, int i)
{
	char	*tmp;
	char	*str;
	int		j;
	int		k;
	int		l;

	j = i + 1;
	k = 0;
	l = 0;
	while ((arg[j] >= 'a' && arg[j] <= 'z')
			|| (arg[j] >= 'A' && arg[j] <= 'Z'))
		j++;
	if (!(tmp = ft_strsub(arg, i + 1, j - i - 1)))
		return (NULL);
	k = findenv(env, tmp);
	str = (env[0][k] != NULL) ? ft_strjoin(env[0][k] + ft_strlen(tmp) + 1,
			arg + j) : ft_strdup(arg + j);
	ft_strdel(&tmp);
	return (editarg(arg, str, i));
}

char			*sendhome(char *arg, char *path)
{
	char	*final;
	int		i;

	i = 0;
	if (!(final = ft_strjoin(path, arg + (i + 1))))
	{
		ft_strdel(&path);
		return (NULL);
	}
	ft_strdel(&path);
	ft_strdel(&arg);
	return (final);
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
	int		i;

	i = 0;
	if (arg && *arg && arg[i] == '~' && (tmp = get_home(env)))
		return (sendhome(arg, tmp));
	while (arg && *arg && arg[i] != '\0')
	{
		if (arg[i] == '$')
		{
			arg = expand_var(arg, env, i);
			i = 0;
		}
		++i;
	}
	return (arg);
}
