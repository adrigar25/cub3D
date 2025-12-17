/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:03:35 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:54:11 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FUNCION: ft_strchr
** -----------------
** Busca la primera aparición del carácter c en la cadena s.
**
** PARAMETROS:
** - const char *s: La cadena en la que se busca el carácter.
** - int c: El carácter a buscar.
**
** RETORNO:
** - Un puntero a la primera aparición del carácter c en la cadena s.
** - NULL si el carácter no se encuentra.
**
*/

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}
