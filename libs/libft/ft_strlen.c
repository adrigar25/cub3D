/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:08:33 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:56:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_strlen
** -----------------
** Calcula la longitud de la cadena str.
**
** PARAMETROS:
** - const char *str: La cadena cuya longitud se va a calcular.
**
** RETORNO:
** - La longitud de la cadena str (sin incluir el carácter nulo).
**
*/

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}
