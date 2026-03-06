/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:43:02 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/17 01:02:16 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ENGLISH: Outputs an integer to the specified file descriptor.
 *
 * SPANISH: Envía un entero al descriptor de archivo especificado.
 *
 * @param n   The integer to output. /
 *            El entero a enviar.
 *
 * @param fd  The file descriptor where the integer will be written. /
 *            El descriptor de archivo donde se escribirá el entero.
 *
 * @returns The number of characters written, or -1 on failure. /
 *          El número de caracteres escritos, o -1 en caso de error.
 */
int	ft_putnbr_fd(long n, int fd)
{
	char	buf[32];
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (n == 0)
		return (write(fd, "0", 1));
	if (n < 0)
	{
		count += write(fd, "-", 1);
		n = -n;
	}
	while (n > 0)
	{
		buf[i++] = '0' + (n % 10);
		n /= 10;
	}
	while (i-- > 0)
		count += write(fd, &buf[i], 1);
	return (count);
}
