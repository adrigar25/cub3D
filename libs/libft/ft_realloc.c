/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:45:00 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/17 16:53:45 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCIÓN: ft_realloc
** ------------------
** Cambia el tamaño de la memoria apuntada por ptr a size bytes.
** Si ptr es NULL, funciona como malloc.
** Si size es 0, funciona como free y retorna NULL.
** Si la reasignación falla, retorna NULL y el bloque original no se modifica.
**
** PARÁMETROS:
** - void *ptr: Puntero a la memoria a redimensionar.
** - size_t size: Nuevo tamaño deseado.
**
** RETORNO:
** - Un puntero a la memoria redimensionada, o NULL si falla.
**
*/

void	*ft_realloc(void *ptr, size_t size)
{
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(size));
	return (realloc(ptr, size));
}
