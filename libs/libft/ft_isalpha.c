/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:11:24 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:38:42 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FUNCION: ft_isalpha
** -----------------
** Comprueba si el carácter c es una letra (mayúscula o minúscula).
**
**
** PARAMETROS:
** - int c: El carácter a comprobar.
**
**
** RETORNO:
** - 1 si c es una letra, 0 en caso contrario.
**
*/

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
