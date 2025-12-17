/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:12:07 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:41:04 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FUNCION: ft_isdigit
** -----------------
** Comprueba si el carácter c es un dígito (0 a 9).
**
** PARAMETROS:
** - int c: El carácter a comprobar.
**
** RETORNO:
** - 1 si c es un dígito, 0 en caso contrario.
**
*/

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
