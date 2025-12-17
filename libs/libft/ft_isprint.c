/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:13:48 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:40:57 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FUNCION: ft_isprint
** -----------------
** Comprueba si el carácter c es un carácter imprimible (32 a 126).
**
** PARAMETROS:
** - int c: El carácter a comprobar.
**
** RETORNO:
** - 1 si c es un carácter imprimible, 0 en caso contrario.
**
*/

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
