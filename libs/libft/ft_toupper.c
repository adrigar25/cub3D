/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:49:01 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:59:18 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FUNCION: ft_toupper
** -----------------
** Convierte un carácter a mayúscula si es una letra minúscula.
**
** PARAMETROS:
** - int c: El carácter a convertir.
**
** RETORNO:
** - El carácter convertido a mayúscula si es una letra minúscula.
** - El carácter original si no es una letra minúscula.
**
*/

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
