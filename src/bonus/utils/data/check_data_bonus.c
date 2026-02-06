#include "../../cub3d_bonus.h"

static int	check_texture_file(char *path, char *label)
{
	if (!path || access(path, F_OK) == -1)
	{
		ft_fprintf(2, RED "Error: %s texture file not found\n" RESET, label);
		return (-1);
	}
	return (0);
}


static int	check_colors(t_game *game)
{
	if (game->floor_color == -1 || game->ceiling_color == -1)
	{
		ft_fprintf(2, RED "Error: Missing floor or ceiling color\n" RESET);
		return (-1);
	}
	if (game->ceiling_color == -2)
		return (ft_fprintf(2, RED "Error: Invalid ceiling RGB\n" RESET), -1);
	if (game->floor_color == -2)
		return (ft_fprintf(2, RED "Error: Invalid floor RGB\n" RESET), -1);
	return (0);
}

int	check_data(t_game *game_data)
{
	t_texture	*current;

	if (!game_data->txt_no || !game_data->txt_so
		|| !game_data->txt_we || !game_data->txt_ea)
		return (ft_fprintf(2, RED "Error: faltan texturas NO/SO/WE/EA\n" RESET),
			-1);
	if (check_texture_file(game_data->txt_no->path, "North") == -1)
		return (-1);
	if (check_texture_file(game_data->txt_so->path, "South") == -1)
		return (-1);
	if (check_texture_file(game_data->txt_we->path, "West") == -1)
		return (-1);
	if (check_texture_file(game_data->txt_ea->path, "East") == -1)
		return (-1);
	if (game_data->txt_door &&
		check_texture_file(game_data->txt_door->path, "Door") == -1)
		return (-1);
	current = game_data->sprites;
	while (current)
	{
		if (check_texture_file(current->path, current->name) == -1)
			return (-1);
		current = current->next;
	}
	if (check_colors(game_data) == -1)
		return (-1);
	return (0);
}
