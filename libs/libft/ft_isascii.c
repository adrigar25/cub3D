/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:20:31 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:39:06 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FUNCION: ft_isascii
** -----------------
** Comprueba si el carácter c es un carácter ASCII (0 a 127).
**
**
** PARAMETROS:
** - int c: El carácter a comprobar.
**
**
** RETORNO:
** - 1 si c es un carácter ASCII, 0 en caso contrario.
**
*/

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
