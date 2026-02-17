/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:30:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/17 18:24:00 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_BONUS_H
# define DEFINES_BONUS_H

/* ========== COLOR CONSOLE ========== */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define ORANGE "\033[38;5;208m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

/* ========== KEY MAPPING - MACOS ========== */
# define KEY_W_M 13
# define KEY_A_M 2
# define KEY_S_M 1
# define KEY_D_M 0
# define KEY_LEFT_M 124
# define KEY_RIGHT_M 123
# define KEY_UP_M 126
# define KEY_DOWN_M 125
# define KEY_ESC_M 53
# define KEY_E_M 14
# define KEY_CTRL_M 256
# define KEY_SHIFT_M 257

/* ========== KEY MAPPING - LINUX ========== */
# define KEY_W_L 119
# define KEY_A_L 97
# define KEY_S_L 115
# define KEY_D_L 100
# define KEY_LEFT_L 65361
# define KEY_RIGHT_L 65363
# define KEY_UP_L 65362
# define KEY_DOWN_L 65364
# define KEY_ESC_L 65307
# define KEY_E_L 101
# define KEY_CTRL_L 65507
# define KEY_SHIFT_L 65505

/* ========== SHADOW & EFFECTS ========== */
# define SHADOW_MASK 0x7F7F7F

/* ========== WINDOW DIMENSIONS ========== */
# ifndef WIN_W
#  define WIN_W 1280
# endif

# ifndef WIN_H
#  define WIN_H 720
# endif

/* ========== TEXTURE CONSTANTS ========== */
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

#endif /* DEFINES_BONUS_H */
