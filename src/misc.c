/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:25:44 by guroux            #+#    #+#             */
/*   Updated: 2019/08/12 18:44:22 by guroux           ###   ########.fr       */
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

int		reppwd(char ***env, char *pwd, int i)
{
	while (env[0][i])
	{
		if (ft_strncmp("PWD", env[0][i], ft_strlen("PWD")) == 0)
		{
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
