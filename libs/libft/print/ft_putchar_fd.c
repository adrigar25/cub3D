/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:56:33 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/17 01:02:16 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ENGLISH: Outputs a character to the given file descriptor.
 *
 * SPANISH: Escribe un carácter en el descriptor de archivo dado.
 *
 * @param c     The character to output. /
 *              El carácter a escribir.
 *
 * @param fd    The file descriptor where the character will be written. /
 *              El descriptor de archivo donde se escribirá el carácter.
 *
 * @returns     0 on success, -1 on failure. /
 *              0 en caso de éxito, -1 en caso de error.
 */
int	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (0);
}
