/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_minimap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asato <asato@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 19:44:08 by asato             #+#    #+#             */
/*   Updated: 2026/07/02 12:34:32 by asato            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "exec.h"
#include <mlx.h>

void	render_tile(t_game *game, t_tile tile, int size)
{
	int	i;
	int	j;

	i = tile.y;
	while (i < tile.y + size)
	{
		j = tile.x;
		while (j < tile.x + size)
			img_pix_put(&game->exec.scre, j++, i, tile.color);
		++i;
	}
}

t_pos	convert(t_vec a)
{
	t_pos	result;

	result.col = (int)(a.x * (double)TILE_SIZE);
	result.row = (int)(a.y * (double)TILE_SIZE);
	return (result);
}

int	find_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
