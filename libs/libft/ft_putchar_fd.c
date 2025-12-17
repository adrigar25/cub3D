/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:05:02 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:51:34 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_putchar_fd
** -----------------
** Escribe el carácter c en el descriptor de archivo fd.
**
** PARAMETROS:
** - char c: El carácter a escribir.
** - int fd: El descriptor de archivo donde se escribirá el carácter.
**
** RETORNO:
** - Ninguno.
**
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
