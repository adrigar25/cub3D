/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:20:23 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 23:17:01 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_lstnew
** -----------------
** Crea un nuevo nodo de la lista enlazada.
**
** PARAMETROS:
** - void *content: Contenido del nuevo nodo.
**
** RETORNO:
** - Puntero al nuevo nodo creado.
** - NULL si la reserva de memoria falla.
**
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
