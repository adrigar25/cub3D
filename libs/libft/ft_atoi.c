/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:44:45 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:36:08 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** FUNCIÓN: ft_atoi
** -----------------
** Convierte una cadena de caracteres en un número entero.
**
** PARÁMETROS:
** - const char *nptr: La cadena de caracteres a convertir.
**
** RETORNO:
** - El número entero resultante de la conversión.
**
** DESCRIPCIÓN:
** - La función ignora los espacios en blanco al principio de la cadena.
** - Si encuentra un signo '+' o '-', lo considera para determinar el signo
**   del número.
** - Convierte los dígitos de la cadena en un número entero.
** - La conversión se detiene al encontrar un carácter no numérico.
** - La función no maneja errores de conversión ni verifica el rango del
**   número resultante.
**
*/

int	ft_atoi(const char *nptr)
{
	int	result;

	result = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n' || *nptr == '\v'
		|| *nptr == '\f' || *nptr == '\r')
		nptr++;
	if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9' && *nptr != '\0')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result);
}
