/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:45:00 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/17 22:38:51 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCIÓN: ft_realloc
** ------------------
** Cambia el tamaño de la memoria apuntada por ptr a new_size bytes.
** Si ptr es NULL, funciona como malloc.
** Si new_size es 0, funciona como free y retorna NULL.
** Si la reasignación falla, retorna NULL y el bloque original no se modifica.
**
** PARÁMETROS:
** - void *ptr: Puntero a la memoria a redimensionar.
** - size_t old_size: Tamaño actual del bloque de memoria.
** - size_t new_size: Nuevo tamaño deseado.
**
** RETORNO:
** - Un puntero a la memoria redimensionada, o NULL si falla.
**
*/

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}
