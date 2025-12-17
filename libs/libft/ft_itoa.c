/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:10:52 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:41:48 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_itoa
** -----------------
** Convierte un número entero en una cadena de caracteres.
**
** PARAMETROS:
** - int n: El número entero a convertir.
**
** RETORNO:
** - Un puntero a la cadena de caracteres resultante.
** - NULL si la reserva de memoria falla.
**
*/

static int	get_length(int n)
{
	int	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	fill_str(char *str, unsigned int num, int len, int sign)
{
	str[len] = '\0';
	while (len--)
	{
		str[len] = (num % 10) + '0';
		num /= 10;
	}
	if (sign)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	int				sign;
	unsigned int	num;

	sign = (n < 0);
	if (n < 0)
		num = -n;
	else
		num = n;
	len = get_length(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	fill_str(str, num, len, sign);
	return (str);
}
