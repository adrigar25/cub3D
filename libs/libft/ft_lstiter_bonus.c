/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:39:39 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:46:19 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_lstiter
** -----------------
** Aplica la función f a cada elemento de la lista enlazada lst.
**
** PARAMETROS:
** - t_list *lst: Puntero a la lista enlazada.
** - void (*f)(void *): Función a aplicar a cada elemento.
**
** RETORNO:
** - Ninguno.
**
*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
