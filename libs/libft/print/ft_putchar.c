/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:41:56 by adriescr          #+#    #+#             */
/*   Updated: 2026/02/17 01:02:16 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ENGLISH: Outputs a character to the standard output.
 *
 * SPANISH: Envía un carácter a la salida estándar.
 *
 * @param c   The character to output. /
 *            El carácter a enviar.
 *
 * @returns 0 on success, -1 on failure. /
 *          0 en caso de éxito, -1 en caso de error.
 */
int	ft_putchar(char c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (0);
}
