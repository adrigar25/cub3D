/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:37:41 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:43:23 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_lstclear
** -----------------
** Libera la memoria de todos los elementos de la lista enlazada y
** establece el puntero a la lista en NULL.
**
** PARAMETROS:
** - t_list **lst: Doble puntero a la lista enlazada.
** - void (*del)(void *): Función para liberar el contenido de cada elemento.
**
** RETORNO:
** - Ninguno.
**
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
