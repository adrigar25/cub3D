/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:26:17 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:46:55 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_lstlast
** -----------------
** Devuelve el último elemento de la lista enlazada.
**
** PARAMETROS:
** - t_list *lst: Puntero a la lista enlazada.
**
** RETORNO:
** - Puntero al último elemento de la lista.
**
*/

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
