/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:50:37 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:57:02 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_strmapi
** -----------------
** Aplica la función f a cada carácter de la cadena s, pasando su índice
** como primer argumento, y crea una nueva cadena con los resultados.
**
** PARAMETROS:
** - char const *s: La cadena a modificar.
** - char (*f)(unsigned int, char): La función a aplicar a cada carácter.
**
** RETORNO:
** - Un puntero a la nueva cadena resultante.
** - NULL si la reserva de memoria falla o si s es NULL.
**
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
