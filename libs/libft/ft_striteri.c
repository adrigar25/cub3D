/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:48:10 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:55:02 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FUNCION: ft_striteri
** -----------------
** Aplica la función f a cada carácter de la cadena s, pasando su índice
** como primer argumento.
**
** PARAMETROS:
** - char *s: La cadena a modificar.
** - void (*f)(unsigned int, char *): La función a aplicar a cada carácter.
**
** RETORNO:
** - Ninguno.
**
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
