/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:09:15 by agarcia           #+#    #+#             */
/*   Updated: 2025/06/23 16:32:46 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_putstr_fd
** -----------------
** Escribe la cadena s en el descriptor de archivo fd.
**
** PARAMETROS:
** - char *s: La cadena a escribir.
** - int fd: El descriptor de archivo donde se escribirá la cadena.
**
** RETORNO:
** - Ninguno.
**
*/

void	ft_putstr_fd(const char *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}
