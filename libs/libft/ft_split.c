/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 20:25:36 by agarcia           #+#    #+#             */
/*   Updated: 2025/04/23 17:53:41 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FUNCION: ft_split
** -----------------
** Divide una cadena en subcadenas utilizando un delimitador dado.
**
** PARAMETROS:
** - char const *s: La cadena a dividir.
** - char c: El delimitador utilizado para dividir la cadena.
**
** RETORNO:
** - Un puntero a un array de cadenas (subcadenas).
** - NULL si la reserva de memoria falla o si la cadena de entrada es NULL.
**
*/
static int	ft_wordcount(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static void	free_result(char **result, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

static int	fill_result(char **result, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			k = i;
			while (s[i] && s[i] != c)
				i++;
			result[j] = ft_substr(s, k, i - k);
			if (!result[j++])
			{
				free_result(result, j - 1);
				return (0);
			}
		}
		else
			i++;
	}
	result[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!result)
		return (NULL);
	if (!fill_result(result, s, c))
		return (NULL);
	return (result);
}
