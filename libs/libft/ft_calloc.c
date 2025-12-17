/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:53:44 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 18:05:09 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCIÓN: ft_calloc
** -----------------
** Reserva memoria para un array de nmemb elementos de size bytes cada uno
** y la inicializa a cero.
**
** PARÁMETROS:
** - size_t nmemb: Número de elementos a reservar.
** - size_t size: Tamaño de cada elemento en bytes.
**
** RETORNO:
** - Un puntero a la memoria reservada, o NULL si la reserva falla.
**
*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
