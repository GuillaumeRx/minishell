/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 02:02:20 by guroux            #+#    #+#             */
/*   Updated: 2019/06/28 03:13:12 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void loop(void)
{
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		ft_putstr("$> ");
		args = getargs();
		// TODO : Free args tab
		status = execute(args);
	}
	
}

int		main(void)
{
	loop();
}