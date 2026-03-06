/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:34:30 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/17 01:02:16 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ENGLISH: Outputs a string to the given file descriptor.
 *
 * SPANISH: Escribe una cadena de caracteres en el descriptor de archivo dado.
 *
 * @param s     The string to output. /
 *              La cadena de caracteres a escribir.
 *
 * @param fd    The file descriptor where the string will be written. /
 *              El descriptor de archivo donde se escribirá la cadena.
 *
 * @returns     None. /
 *              Ninguno.
 */
int	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return (0);
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	return (1);
}
