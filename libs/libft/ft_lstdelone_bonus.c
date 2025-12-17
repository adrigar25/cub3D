/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:31:20 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:45:36 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_lstdelone
** -----------------
** Libera la memoria del contenido de un elemento de la lista enlazada y
** libera el propio elemento.
**
** PARAMETROS:
** - t_list *lst: Puntero al elemento a liberar.
** - void (*del)(void *): Función para liberar el contenido del elemento.
**
** RETORNO:
** - Ninguno.
**
*/
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
