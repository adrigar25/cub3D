/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:27:43 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:42:11 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_lstadd_back
** -----------------
** Añade un nuevo elemento al final de la lista enlazada.
**
** PARAMETROS:
** - t_list **lst: Doble puntero a la lista enlazada.
** - t_list *new: Puntero al nuevo elemento a añadir.
**
** RETORNO:
** - Ninguno.
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}
