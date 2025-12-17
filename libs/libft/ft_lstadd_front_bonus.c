/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:22:26 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:42:46 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_lstadd_front
** -----------------
** Añade un nuevo elemento al principio de la lista enlazada.
**
** PARAMETROS:
** - t_list **lst: Doble puntero a la lista enlazada.
** - t_list *new: Puntero al nuevo elemento a añadir.
**
** RETORNO:
** - Ninguno.
**
*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
