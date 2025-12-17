/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:12:52 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:37:24 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FUNCION: ft_isalnum
** -----------------
** Comprueba si el carácter c es alfanumérico (letra o dígito).
**
** PARAMETROS:
** - int c: El carácter a comprobar.
**
** RETORNO:
** - 1 si c es alfanumérico, 0 en caso contrario.
**
*/

int	ft_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9'));
}
