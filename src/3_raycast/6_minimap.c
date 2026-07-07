/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_minimap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asato <asato@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 17:51:57 by asato             #+#    #+#             */
/*   Updated: 2026/07/01 18:58:10 by asato            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "exec.h"
#include <math.h>/*for pi*/
#include <mlx.h>

static void	draw_vision_line(t_map map, t_data *screen,
							t_play play, t_vec ray_dir)
{
	t_pos	point;
	t_pos	max;
	int		fan_max;
	double	t;

	max = (t_pos){.col = map.width * TILE_SIZE, .row = map.height * TILE_SIZE};
	fan_max = find_max(max.row, max.col);
	t = 0.0;
	while (t <= fan_max)
	{
		point = convert(add_vec(play.pos, mult_vec(t, ray_dir)));
		if (point.col >= max.col || point.row >= max.row || point.col < 0
			|| point.row < 0 || map.grid[point.row / TILE_SIZE][point.col
			/ TILE_SIZE] == '1')
			break ;
		img_pix_put(screen, point.col, point.row, FAN_COLOR);
		t += 0.01;
	}
}

void	display_vision_cone(t_map map, t_data *screen, t_play play)
{
	t_vec	ray_dir;
	double	angle;

	angle = (M_PI / 6) * -1;
	play.pos.x += 0.2;
	play.pos.y += 0.2;
	while (angle < M_PI / 6)
	{
		ray_dir = turn_vec(play.dir, angle);
		draw_vision_line(map, screen, play, ray_dir);
		angle += 0.01;
	}
}

static int	set_tile_color(char c)
{
	if (c == '1')
		return (WALL_COLOR);
	if (c == '0')
		return (FLOOR_COLOR);
	return (-1);
}

void	draw_tiles(t_game *game)
{
	int		row;
	int		col;
	int		color;
	t_tile	tile;

	tile = (t_tile){.x = 0, .y = 0, .color = 0};
	row = 0;
	while (row < game->map.height)
	{
		col = 0;
		while (game->map.grid[row][col] != '\0')
		{
			color = set_tile_color(game->map.grid[row][col]);
			if (color != -1)
			{
				tile.y = row * TILE_SIZE;
				tile.x = col * TILE_SIZE;
				tile.color = color;
				render_tile(game, tile, TILE_SIZE);
			}
			col++;
		}
		row++;
	}
}

void	draw_player(t_game *game)
{
	t_tile	player;

	player.x = game->exec.play.pos.x * TILE_SIZE;
	player.y = game->exec.play.pos.y * TILE_SIZE;
	player.color = PLAYER_COLOR;
	render_tile(game, player, PLAYER_SIZE);
}
