/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtaballoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 12:14:12 by guroux            #+#    #+#             */
/*   Updated: 2019/08/13 17:20:42 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dtaballoc(int size)
{
	char	**tab;

	if (!(tab = (char **)malloc(sizeof(char *) * size)))
		return (NULL);
	tab[size - 1] = 0;
	return (tab);
}
