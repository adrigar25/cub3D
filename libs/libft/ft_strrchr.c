/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:03:35 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:57:45 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FUNCION: ft_strrchr
** -----------------
** Busca la última aparición del carácter c en la cadena s.
**
** PARAMETROS:
** - const char *s: La cadena en la que se busca el carácter.
** - int c: El carácter a buscar.
**
** RETORNO:
** - Un puntero a la última aparición del carácter c en la cadena s.
** - NULL si el carácter no se encuentra.
**
*/

char	*ft_strrchr(const char *s, int c)
{
	char	*d;

	d = 0;
	while (*s != '\0')
	{
		if (*s == (char)c)
			d = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (d);
}
