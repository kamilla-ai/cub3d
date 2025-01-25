/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:10:49 by krazikho          #+#    #+#             */
/*   Updated: 2025/01/15 17:19:41 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	update_position(t_game *game, int dx, int dy)
{
	game->pl_x_tile += dx;
	game->pl_x = game->pl_x_tile / TILE_SIZE;
	game->pl_y_tile += dy;
	game->pl_y = game->pl_y_tile / TILE_SIZE;
}

static void	move_forward_or_backward(t_game *game, int keycode)
{
	double	dy;
	double	dx;
	int		grid_y;
	int		grid_x;

	if (keycode == 13)
	{
		dy = -sin(game->pl_view_ang) * SPEED;
		dx = cos(game->pl_view_ang) * SPEED;
	}
	else
	{
		dy = sin(game->pl_view_ang) * SPEED;
		dx = -cos(game->pl_view_ang) * SPEED;
	}
	grid_y = (int)((game->pl_y_tile + dy) / TILE_SIZE);
	grid_x = (int)((game->pl_x_tile + dx) / TILE_SIZE);
	if (grid_x != (int)t_strlen(game->map[grid_y])
		&& game->map[grid_y][grid_x] != '1' && game->map[grid_y][grid_x] != ' ')
	{
		if (game->map[game->pl_y][grid_x] == '1'
		&& game->map[grid_y][game->pl_x] == '1')
			return ;
		update_position(game, dx, dy);
	}
}

static void	move_right_left(t_game *game, int keycode)
{
	double	angle;
	double	dx;
	double	dy;
	int		grid_y;
	int		grid_x;

	if (keycode == 2)
		angle = game->pl_view_ang - M_PI / 2;
	if (keycode == 0)
		angle = game->pl_view_ang + M_PI / 2;
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	dy = -sin(angle) * SPEED;
	dx = cos(angle) * SPEED;
	grid_y = (int)((game->pl_y_tile + dy) / TILE_SIZE);
	grid_x = (int)((game->pl_x_tile + dx) / TILE_SIZE);
	if (grid_x != (int)t_strlen(game->map[grid_y])
		&& game->map[grid_y][grid_x] != '1' && game->map[grid_y][grid_x] != ' ')
	{
		game->pl_x_tile += dx;
		game->pl_x = game->pl_x_tile / TILE_SIZE;
		game->pl_y_tile += dy;
		game->pl_y = game->pl_y_tile / TILE_SIZE;
	}
}

static void	change_angle_of_view(t_game *game, int keycode)
{
	if (keycode == 123)
		game->pl_view_ang = game->pl_view_ang + 0.135;
	if (keycode == 124)
		game->pl_view_ang = game->pl_view_ang - 0.135;
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 13 || keycode == 1)
		move_forward_or_backward(game, keycode);
	if (keycode == 2 || keycode == 0)
		move_right_left(game, keycode);
	if (keycode == 123 || keycode == 124)
		change_angle_of_view(game, keycode);
	if (keycode == 53)
		free_game_success(game);
	draw(game);
	return (1);
}
