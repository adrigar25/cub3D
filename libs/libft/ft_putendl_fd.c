/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:12:07 by agarcia           #+#    #+#             */
/*   Updated: 2025/05/18 19:20:59 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_putendl_fd
** -----------------
** Escribe la cadena s en el descriptor de archivo fd, seguida de un salto
** de línea.
**
** PARAMETROS:
** - char *s: La cadena a escribir.
** - int fd: El descriptor de archivo donde se escribirá la cadena.
**
** RETORNO:
** - Ninguno.
**
*/

void	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
