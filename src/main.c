/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 02:02:20 by guroux            #+#    #+#             */
/*   Updated: 2019/07/17 20:56:40 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void loop(char ***env)
{
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		ft_putstr("$> ");
		args = getargs();
		// TODO : Free args tab
		status = execute(args, env);
		deltab(args);
	}
}

int		main(int ac, char **av, char **envp)
{
	char **env;

	(void)ac;
	(void)av;
	env = copyenv(envp);
	loop(&env);
	deltab(env);
	return (0);
}
