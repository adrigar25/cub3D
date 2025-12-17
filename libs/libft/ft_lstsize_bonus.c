/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:25:12 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:48:24 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_lstsize
** -----------------
** Devuelve el número de elementos en la lista enlazada.
**
** PARAMETROS:
** - t_list *lst: Puntero a la lista enlazada.
**
** RETORNO:
** - El número de elementos en la lista enlazada.
**
*/

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
