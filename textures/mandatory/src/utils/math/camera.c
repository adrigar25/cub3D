/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriescr <adriescr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:46:17 by agarcia           #+#    #+#             */
/*   Updated: 2026/02/23 16:01:54 by adriescr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

/**
 * ENGLISH: Converts a screen column index to a camera-plane x coordinate
 * 			in the range [-1, 1].
 *
 * SPANISH: Convierte un índice de columna de pantalla a una coordenada x
 * 			del plano de cámara en el rango [-1, 1].
 *
 * @param x The screen column index. / El índice de columna en pantalla.
 * @param win_w The window width in pixels. / El ancho de ventana en píxeles.
 *
 * @return The camera-plane x coordinate. / La coordenada x del plano.
 */
double	camera_x(int x, int win_w)
{
	return (2.0 * x / (double)win_w - 1.0);
}
