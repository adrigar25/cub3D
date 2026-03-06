/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/18 21:06:13 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLE_H
# define CONSOLE_H

/*
** console.h — ANSI terminal color macros and colored print utilities.
** Completely independent: no project-specific types, no external libs.
*/

/* ========== CONSOLE COLOR DEFINES ========== */
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define ORANGE		"\033[38;5;208m"
# define BLUE		"\033[0;34m"
# define MAGENTA	"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"
# define RESET		"\033[0m"

/* ========== PRINT UTILITIES ========== */
long	ft_error(const char *function, char **str);
long	ft_putcolor(int fd, int color);
long	ft_putstr_fd_color(const char *str, int fd, int color);

#endif /* CONSOLE_H */
