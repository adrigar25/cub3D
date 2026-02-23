/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_characters_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:10:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:55 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "console_bonus.h"
#include "game_bonus.h"
#include "libft.h"
#include "map_bonus.h"

/**
 * ENGLISH: Returns 1 if character c is in the game's current list of
 *          allowed map characters.
 *
 * SPANISH: Retorna 1 si el carácter c está en la lista actual de
 *          carácteres de mapa permitidos del juego.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 * @param c Character to test. / Carácter a probar.
 *
 * @return 1 if allowed, 0 otherwise. / 1 si está permitido, 0 si no.
 */
static int	is_allowed_char(t_game *game, char c)
{
	int	i;

	if (!game)
		return (0);
	i = 0;
	while (i < game->allowed_count)
	{
		if (game->allowed_chars[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * ENGLISH: Iterates over every cell in the map grid and verifies that
 *          each character is in the allowed-characters list.
 *
 * SPANISH: Itera sobre cada celda de la cuadrícula del mapa y verifica
 *          que cada carácter esté en la lista de carácteres permitidos.
 *
 * @param game Pointer to the game structure. /
 *             Puntero a la estructura del juego.
 *
 * @return 0 on success, -1 if an invalid character is found. /
 *         0 en éxito, -1 si se encuentra un carácter inválido.
 */
int	check_valid_characters(t_game *game)
{
	int	i;
	int	j;

	if (!game || !game->map.grid)
		return (-1);
	i = -1;
	while (game->map.grid[++i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (!is_allowed_char(game, game->map.grid[i][j]))
			{
				ft_fprintf(2, RED "Error: Invalid character '%c' ",
					game->map.grid[i][j]);
				ft_fprintf(2, "at row %d, col %d\n" RESET, i + 1, j + 1);
				return (-1);
			}
			j++;
		}
	}
	return (0);
}
