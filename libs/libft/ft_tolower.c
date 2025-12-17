/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:49:01 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:58:57 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FUNCION: ft_tolower
** -----------------
** Convierte un carácter a minúscula si es una letra mayúscula.
**
** PARAMETROS:
** - int c: El carácter a convertir.
**
** RETORNO:
** - El carácter convertido a minúscula si es una letra mayúscula.
** - El carácter original si no es una letra mayúscula.
**
*/

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
