/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:41:35 by agarcia           #+#    #+#             */
/*   Updated: 2026/01/29 02:40:13 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	valid_extension(const char *filename, const char *extension)
{
	size_t	filename_len;
	size_t	extension_len;
	const char	*file_ext;
	int		i;

	if (!filename || !extension)
		return (0);
	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(extension);
	if (filename_len < extension_len)
		return (0);
	// Buscar el último punto en el nombre del archivo
	file_ext = NULL;
	i = filename_len - 1;
	while (i >= 0)
	{
		if (filename[i] == '.')
		{
			file_ext = &filename[i];
			break;
		}
		i--;
	}
	if (!file_ext)
		return (0);
	// Verificar que la extensión coincida exactamente
	return (ft_strcmp(file_ext, extension) == 0);
}

static void	print_usage(const char *program_name)
{
	ft_fprintf(1, "Usage: %s <map_file.cub> [options]\n", program_name);
	ft_fprintf(1, "\nOptions:\n");
	ft_fprintf(1, "  -s <port>           Start as server on specified port (default: 8080)\n");
	ft_fprintf(1, "  -c <ip> <port>      Connect to server at IP:port\n");
	ft_fprintf(1, "\nExamples:\n");
	ft_fprintf(1, "  %s map.cub                    # Single player\n", program_name);
	ft_fprintf(1, "  %s map.cub -s 8080           # Server mode\n", program_name);
	ft_fprintf(1, "  %s map.cub -c 192.168.1.5 8080  # Client mode\n", program_name);
}

int	cub3d(char *file, int is_server, const char *ip, int port)
{
	t_game	*game_data;

	game_data = init_data();
	if (read_data(&game_data, file))
		return (clear_game(game_data), 1);
	if (check_data(game_data))
		return (clear_game(game_data), 1);
	if (check_map(game_data->map))
		return (clear_game(game_data), 1);
	if (init_mlx(game_data))
		return (clear_game(game_data), 1);
	if (load_textures_images(game_data))
		return (clear_game(game_data), 1);
	if (get_player_position(game_data))
		return (clear_game(game_data), 1);
	
	// Inicializar networking si es necesario
	if (is_server != -1) // Si no es modo single player
	{
		if (init_network(game_data, is_server, ip, port) != 0)
		{
			ft_fprintf(2, RED "Failed to initialize networking\n" RESET);
			return (clear_game(game_data), 1);
		}
	}
	
	start_game_loop(game_data);
	return (0);
}

int	main(int argc, char **argv)
{
	int			is_server = -1;  // -1 = single player, 0 = client, 1 = server
	const char	*ip = NULL;
	int			port = 8080;  // DEFAULT_PORT
	
	if (argc < 2)
	{
		print_usage(argv[0]);
		return (-1);
	}
	
	if (!valid_extension(argv[1], ".cub"))
	{
		ft_fprintf(2, RED "Error: Map file must have a .cub extension\n" RESET);
		return (-1);
	}

	// Parse command line arguments
	if (argc > 2)
	{
		if (ft_strcmp(argv[2], "-s") == 0)
		{
			// Server mode
			is_server = 1;
			if (argc > 3)
				port = ft_atoi(argv[3]);
		}
		else if (ft_strcmp(argv[2], "-c") == 0)
		{
			// Client mode
			is_server = 0;
			if (argc < 4)
			{
				ft_fprintf(2, RED "Error: Client mode requires server IP\n" RESET);
				print_usage(argv[0]);
				return (-1);
			}
			ip = argv[3];
			if (argc > 4)
				port = ft_atoi(argv[4]);
		}
		else
		{
			ft_fprintf(2, RED "Error: Invalid option '%s'\n" RESET, argv[2]);
			print_usage(argv[0]);
			return (-1);
		}
	}

	if (is_server == 1)
		ft_fprintf(1, GREEN "Starting server on port %d\n" RESET, port);
	else if (is_server == 0)
		ft_fprintf(1, GREEN "Connecting to server %s:%d\n" RESET, ip, port);
	else
		ft_fprintf(1, GREEN "Starting single player mode\n" RESET);

	return (cub3d(argv[1], is_server, ip, port));
}
