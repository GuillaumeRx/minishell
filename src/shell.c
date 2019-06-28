/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 02:52:02 by guroux            #+#    #+#             */
/*   Updated: 2019/06/28 03:15:24 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	launch(char **args)
{
	// pid_t	pid;
	// pid_t	wpid;
	// int		status;

	// pid = fork();
	// if (!pid)
	while (*args)
	{
		ft_putendl(*args);
		args++;
	}
	return (1);
}

int			execute(char **args)
{
	if (!args[0])
		return 1;
	// TODO : check if its a builtin
	return (launch(args));
}