/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:43:49 by agarcia           #+#    #+#             */
/*   Updated: 2025/12/17 16:08:40 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int handle_error(const char *message)
{
    if (message)
        fprintf(stderr, "Error: %s\n", message);
    else
        perror("Error");
    return -1;
}