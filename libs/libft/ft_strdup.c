/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:51:43 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:54:36 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_strdup
** -----------------
** Duplica la cadena s y devuelve un puntero a la nueva cadena.
**
** PARAMETROS:
** - const char *s: La cadena a duplicar.
**
** RETORNO:
** - Un puntero a la nueva cadena duplicada.
** - NULL si la reserva de memoria falla.
**
*/
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (0);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}
