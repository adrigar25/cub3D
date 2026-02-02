/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:30:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/02 19:03:07 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * Render the menu on screen
 */
void	render_menu(t_game *game)
{
	int y_offset;
	char *title = "CUB3D - MULTIPLAYER";
	char *option1 = "1. Single Player";
	char *option2 = "2. Multiplayer";
	char *controls = "Use ARROW KEYS to navigate, ENTER to select, ESC to quit";

	if (!game || !game->mlx_ptr || !game->win_ptr)
		return;

	// Clear screen
	mlx_clear_window(game->mlx_ptr, game->win_ptr);

	y_offset = WIN_HEIGHT / 4;

	// Draw title
	mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 100, y_offset, 0xFFFFFF, title);

	y_offset += 80;

	// Draw menu options with selection highlight
	if (game->menu.selected_option == 0)
		mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 80, y_offset, 0x00FF00, option1);
	else
		mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 80, y_offset, 0xFFFFFF, option1);

	y_offset += 40;

	if (game->menu.selected_option == 1)
		mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 80, y_offset, 0x00FF00, option2);
	else
		mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 80, y_offset, 0xFFFFFF, option2);

	y_offset += 100;

	// Draw controls
	mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 200, y_offset, 0xAAAAAA, controls);
}

/**
 * Handle menu key input
 */
void	handle_menu_key(int keycode, t_game *game)
{
	if (keycode == KEY_UP_M || keycode == KEY_UP_L)
	{
		game->menu.selected_option--;
		if (game->menu.selected_option < 0)
			game->menu.selected_option = 1;
	}
	else if (keycode == KEY_DOWN_M || keycode == KEY_DOWN_L)
	{
		game->menu.selected_option++;
		if (game->menu.selected_option > 1)
			game->menu.selected_option = 0;
	}
	else if (keycode == 36 || keycode == 65293) // ENTER key
	{
		if (game->menu.selected_option == 0) // Single Player
		{
			start_single_player(game);
		}
		else if (game->menu.selected_option == 1) // Multiplayer
		{
			start_multiplayer_menu(game);
		}
	}
	else if (keycode == KEY_ESC_M || keycode == KEY_ESC_L)
	{
		exit(0);
	}
}

/**
 * Start single player mode - show map selection
 */
void	start_single_player(t_game *game)
{
	start_map_selection(game, 0); // 0 = single player mode
}

/**
 * Show multiplayer submenu
 */
void	start_multiplayer_menu(t_game *game)
{
	game->menu.state = MENU_MULTIPLAYER;
	game->menu.selected_option = 0;
}

/**
 * Render multiplayer menu
 */
void	render_multiplayer_menu(t_game *game)
{
	int y_offset;
	char *title = "MULTIPLAYER MODE";
	char *option1 = "1. Start Server";
	char *option2 = "2. Connect to Server";
	char *option3 = "3. Back to Main Menu";
	char *controls = "Use ARROW KEYS to navigate, ENTER to select, ESC to back";

	if (!game || !game->mlx_ptr || !game->win_ptr)
		return;

	// Clear screen
	mlx_clear_window(game->mlx_ptr, game->win_ptr);

	y_offset = WIN_HEIGHT / 4;

	// Draw title
	mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 80, y_offset, 0xFFFFFF, title);

	y_offset += 80;

	// Draw options with selection highlight
	if (game->menu.selected_option == 0)
		mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 80, y_offset, 0x00FF00, option1);
	else
		mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 80, y_offset, 0xFFFFFF, option1);

	y_offset += 40;

	if (game->menu.selected_option == 1)
		mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 80, y_offset, 0x00FF00, option2);
	else
		mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 80, y_offset, 0xFFFFFF, option2);

	y_offset += 40;

	if (game->menu.selected_option == 2)
		mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 80, y_offset, 0x00FF00, option3);
	else
		mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 80, y_offset, 0xFFFFFF, option3);

	y_offset += 100;

	// Draw controls
	mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 200, y_offset, 0xAAAAAA, controls);
}

/**
 * Handle multiplayer menu input
 */
void	handle_multiplayer_menu_key(int keycode, t_game *game)
{
	if (keycode == KEY_UP_M || keycode == KEY_UP_L)
	{
		game->menu.selected_option--;
		if (game->menu.selected_option < 0)
			game->menu.selected_option = 2;
	}
	else if (keycode == KEY_DOWN_M || keycode == KEY_DOWN_L)
	{
		game->menu.selected_option++;
		if (game->menu.selected_option > 2)
			game->menu.selected_option = 0;
	}
	else if (keycode == 36 || keycode == 65293) // ENTER key
	{
		if (game->menu.selected_option == 0) // Start Server
		{
			start_server(game);
		}
		else if (game->menu.selected_option == 1) // Connect to Server
		{
			connect_to_server(game);
		}
		else if (game->menu.selected_option == 2) // Back to main menu
		{
			game->menu.state = MENU_MAIN;
			game->menu.selected_option = 0;
		}
	}
	else if (keycode == KEY_ESC_M || keycode == KEY_ESC_L)
	{
		game->menu.state = MENU_MAIN;
		game->menu.selected_option = 0;
	}
}

/**
 * Start server mode - show map selection
 */
void	start_server(t_game *game)
{
	start_map_selection(game, 1); // 1 = server mode
}

/**
 * Connect to server - show IP input menu
 */
void	connect_to_server(t_game *game)
{
	start_enter_ip_menu(game);
}

/**
 * Initialize menu system
 */
void	init_menu(t_game *game)
{
	if (!game)
		return;

	game->menu.state = MENU_MAIN;
	game->menu.selected_option = 0;
	game->menu.available_maps = NULL;
	game->menu.map_count = 0;
	game->menu.selected_map = 0;
	game->menu.game_mode = 0;
	game->menu.server_ip[0] = '\0';
	game->menu.ip_cursor = 0;
}

/**
 * Check if a filename ends with .cub
 */
static int	is_cub_file(const char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}

/**
 * Validate if a map is playable
 */
static int	is_valid_map(const char *map_path)
{
	t_game	*temp_game;
	int		valid;
	int		saved_stderr;
	int		dev_null;

	// Silence error messages by redirecting stderr
	saved_stderr = dup(STDERR_FILENO);
	dev_null = open("/dev/null", O_WRONLY);
	dup2(dev_null, STDERR_FILENO);
	close(dev_null);

	temp_game = init_data();
	if (!temp_game)
	{
		dup2(saved_stderr, STDERR_FILENO);
		close(saved_stderr);
		return (0);
	}

	// Try to read and validate the map
	valid = 0;
	if (read_data(&temp_game, (char *)map_path) == 0)
	{
		if (check_data(temp_game) == 0)
		{
			if (check_map(temp_game->map) == 0)
				valid = 1;
		}
	}

	// Clean up temporary game data
	clear_game(temp_game);

	// Restore stderr
	dup2(saved_stderr, STDERR_FILENO);
	close(saved_stderr);

	return (valid);
}

/**
 * Add a map to the available maps list
 */
static void	add_map_to_list(t_game *game, const char *mapname)
{
	char	**new_list;
	int		i;

	new_list = malloc(sizeof(char *) * (game->menu.map_count + 2));
	if (!new_list)
		return;

	i = 0;
	while (i < game->menu.map_count)
	{
		new_list[i] = game->menu.available_maps[i];
		i++;
	}
	new_list[i] = ft_strdup(mapname);
	new_list[i + 1] = NULL;

	if (game->menu.available_maps)
		free(game->menu.available_maps);
	game->menu.available_maps = new_list;
	game->menu.map_count++;
}

/**
 * Load available maps from MAPS directory
 */
void	load_available_maps(t_game *game)
{
	DIR				*dir;
	struct dirent	*entry;

	// Free existing maps if any
	free_available_maps(game);

	// Open MAPS directory
	dir = opendir("MAPS");
	if (!dir)
	{
		printf("Error: Cannot open MAPS directory\n");
		return;
	}

	// Read all .cub files from directory
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (is_cub_file(entry->d_name))
		{
			char map_path[512];
			snprintf(map_path, sizeof(map_path), "MAPS/%s", entry->d_name);

			// Only add valid maps to the list
			if (is_valid_map(map_path))
			{
				add_map_to_list(game, entry->d_name);
			}
		}
		entry = readdir(dir);
	}

	closedir(dir);
	game->menu.selected_map = 0;

	if (game->menu.map_count == 0)
		printf("Warning: No valid maps found in MAPS directory\n");
}

/**
 * Free available maps memory
 */
void	free_available_maps(t_game *game)
{
	int i;

	if (!game->menu.available_maps)
		return;

	i = 0;
	while (i < game->menu.map_count && game->menu.available_maps[i])
	{
		free(game->menu.available_maps[i]);
		i++;
	}
	free(game->menu.available_maps);
	game->menu.available_maps = NULL;
	game->menu.map_count = 0;
}

/**
 * Start map selection menu
 */
void	start_map_selection(t_game *game, int mode)
{
	game->menu.game_mode = mode; // 0=single, 1=server, 2=client
	load_available_maps(game);
	game->menu.state = MENU_MAP_SELECTION;
	game->menu.selected_option = 0;
}

/**
 * Render map selection menu
 */
void	render_map_selection_menu(t_game *game)
{
	int y_offset;
	int i;
	char *title = "SELECT MAP";
	char *back_option = "Back to Menu";
	char *controls = "Use ARROW KEYS to navigate, ENTER to select, ESC to back";

	if (!game || !game->mlx_ptr || !game->win_ptr)
		return;

	// Clear screen
	mlx_clear_window(game->mlx_ptr, game->win_ptr);

	y_offset = WIN_HEIGHT / 5;

	// Draw title
	mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 60, y_offset, 0xFFFFFF, title);

	y_offset += 60;

	// Draw map options
	i = 0;
	while (i < game->menu.map_count && game->menu.available_maps[i])
	{
		if (game->menu.selected_option == i)
			mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 60, y_offset, 0x00FF00, game->menu.available_maps[i]);
		else
			mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 60, y_offset, 0xFFFFFF, game->menu.available_maps[i]);
		y_offset += 35;
		i++;
	}

	y_offset += 20;

	// Draw back option
	if (game->menu.selected_option == game->menu.map_count)
		mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 60, y_offset, 0x00FF00, back_option);
	else
		mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 60, y_offset, 0xFFFFFF, back_option);

	y_offset += 80;

	// Draw controls
	mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 200, y_offset, 0xAAAAAA, controls);
}

/**
 * Handle map selection key input
 */
void	handle_map_selection_key(int keycode, t_game *game)
{
	int max_options = game->menu.map_count; // maps + back option
	char map_path[256];

	if (keycode == KEY_UP_M || keycode == KEY_UP_L)
	{
		game->menu.selected_option--;
		if (game->menu.selected_option < 0)
			game->menu.selected_option = max_options;
	}
	else if (keycode == KEY_DOWN_M || keycode == KEY_DOWN_L)
	{
		game->menu.selected_option++;
		if (game->menu.selected_option > max_options)
			game->menu.selected_option = 0;
	}
	else if (keycode == 36 || keycode == 65293) // ENTER key
	{
		if (game->menu.selected_option == max_options) // Back option
		{
			free_available_maps(game);
			if (game->menu.game_mode == 0) // Single player
			{
				game->menu.state = MENU_MAIN;
			}
			else // Multiplayer modes
			{
				game->menu.state = MENU_MULTIPLAYER;
			}
			game->menu.selected_option = 0;
		}
		else // Map selected
		{
			snprintf(map_path, sizeof(map_path), "MAPS/%s", game->menu.available_maps[game->menu.selected_option]);

			// Load complete game with selected map
			if (read_data(&game, map_path) == 0 &&
				check_data(game) == 0 &&
				check_map(game->map) == 0 &&
				load_textures_images(game) == 0 &&
				get_player_position(game) == 0)
			{
				free_available_maps(game);

				// Initialize network if multiplayer mode
				if (game->menu.game_mode == 1) // Server mode
				{
					printf("Starting server on port %d\n", DEFAULT_PORT);
					if (init_network(game, 1, NULL, DEFAULT_PORT) == 0)
					{
						// Store map name in network structure
						ft_strlcpy(game->network->map_name, 
							game->menu.available_maps[game->menu.selected_option], 256);
						game->menu.state = GAME_RUNNING;
						printf("Server started successfully!\n");
					}
					else
					{
						printf("Failed to start server\n");
						game->menu.state = MENU_MULTIPLAYER;
						game->menu.selected_option = 0;
					}
				}
				else if (game->menu.game_mode == 2) // Client mode (shouldn't happen here)
				{
					game->menu.state = GAME_RUNNING;
				}
				else // Single player
				{
					game->menu.state = GAME_RUNNING;
				}
			}
			else
			{
				printf("Error loading map: %s\n", map_path);
				// Clean up any partial initialization
				free_available_maps(game);
			}
		}
	}
	else if (keycode == KEY_ESC_M || keycode == KEY_ESC_L)
	{
		free_available_maps(game);
		if (game->menu.game_mode == 0) // Single player
		{
			game->menu.state = MENU_MAIN;
		}
		else // Multiplayer modes
		{
			game->menu.state = MENU_MULTIPLAYER;
		}
		game->menu.selected_option = 0;
	}
}

/**
 * Start IP input menu
 */
void	start_enter_ip_menu(t_game *game)
{
	game->menu.state = MENU_ENTER_IP;
	game->menu.server_ip[0] = '\0';
	game->menu.ip_cursor = 0;
}

/**
 * Render IP input menu
 */
void	render_enter_ip_menu(t_game *game)
{
	int y_offset;
	char *title = "CONNECT TO SERVER";
	char *prompt = "Enter server IP address (port 8080):";
	char display_ip[270];
	char *controls = "Type IP address (e.g. 192.168.1.5), ENTER to connect, ESC to cancel";

	if (!game || !game->mlx_ptr || !game->win_ptr)
		return;

	// Clear screen
	mlx_clear_window(game->mlx_ptr, game->win_ptr);

	y_offset = WIN_HEIGHT / 4;

	// Draw title
	mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 100, y_offset, 0xFFFFFF, title);

	y_offset += 80;

	// Draw prompt
	mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 120, y_offset, 0xAAAAAA, prompt);

	y_offset += 50;

	// Draw input field with cursor
	snprintf(display_ip, sizeof(display_ip), "> %s_", game->menu.server_ip);
	mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 150, y_offset, 0x00FF00, display_ip);

	y_offset += 100;

	// Draw controls
	mlx_string_put(game->mlx_ptr, game->win_ptr, WIN_WIDTH / 2 - 200, y_offset, 0xAAAAAA, controls);
}

/**
 * Handle IP input key events
 */
void	handle_enter_ip_key(int keycode, t_game *game)
{
	int len;
	char map_path[256];

	len = ft_strlen(game->menu.server_ip);

	// Handle ENTER key - connect to server
	if (keycode == 36 || keycode == 65293) // ENTER
	{
		if (len > 0)
		{
			// Use default map for client connection
			snprintf(map_path, sizeof(map_path), "MAPS/map1.cub");

			// Load the map and initialize game
			if (read_data(&game, map_path) == 0 &&
				check_data(game) == 0 &&
				check_map(game->map) == 0 &&
				load_textures_images(game) == 0 &&
				get_player_position(game) == 0)
			{
				// Initialize network connection with server_ip
				printf("Connecting to server: %s:%d\n", game->menu.server_ip, DEFAULT_PORT);
				if (init_network(game, 0, game->menu.server_ip, DEFAULT_PORT) == 0)
				{
					game->menu.state = GAME_RUNNING;
					printf("Connected successfully!\n");
				}
				else
				{
					printf("Failed to connect to server\n");
					game->menu.state = MENU_MULTIPLAYER;
					game->menu.server_ip[0] = '\0';
					game->menu.selected_option = 0;
				}
			}
			else
			{
				printf("Error loading game\n");
				game->menu.server_ip[0] = '\0';
				game->menu.ip_cursor = 0;
			}
		}
	}
	// Handle ESC key - cancel
	else if (keycode == KEY_ESC_M || keycode == KEY_ESC_L)
	{
		game->menu.state = MENU_MULTIPLAYER;
		game->menu.selected_option = 0;
	}
	// Handle BACKSPACE
	else if (keycode == 51 || keycode == 65288) // BACKSPACE
	{
		if (len > 0)
			game->menu.server_ip[len - 1] = '\0';
	}
	// Handle character input (numbers, dots, and colons for IPv6)
	else if (len < 255)
	{
		char c = 0;

		// Numbers 0-9 (macOS keycodes)
		if (keycode == 29) // 0
			c = '0';
		else if (keycode == 18) // 1
			c = '1';
		else if (keycode == 19) // 2
			c = '2';
		else if (keycode == 20) // 3
			c = '3';
		else if (keycode == 21) // 4
			c = '4';
		else if (keycode == 23) // 5
			c = '5';
		else if (keycode == 22) // 6
			c = '6';
		else if (keycode == 26) // 7
			c = '7';
		else if (keycode == 28) // 8
			c = '8';
		else if (keycode == 25) // 9
			c = '9';
		else if (keycode == 47) // . (period)
			c = '.';

		if (c != 0)
		{
			game->menu.server_ip[len] = c;
			game->menu.server_ip[len + 1] = '\0';
		}
	}
}
