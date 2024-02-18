/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabou-rk <rabou-rk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:50:55 by rabou-rk          #+#    #+#             */
/*   Updated: 2024/02/18 22:28:08 by rabou-rk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub_bonus.h"

void	draw_rays(t_game *game)
{
	int		j;
	int		i;
	float	angle;
	int		tile_x;
	int		tile_y;

	j = 0;
	tile_x = WIDTH / 2 / game->mx;
	tile_y = HEIGHT / 2 / game->my;
	if (tile_x > 7)
		tile_x = 7;
	if (tile_y > 7)
		tile_y = 7;
	angle = normalize_angle(game->player->player_angle
			- (game->player->fangle / 2));
	while (j < WIDTH)
	{
		i = 0;
		while (i < 400 && !there_is_a_wall(game, game->player->x + cos(angle)
				* i, game->player->y + sin(angle) * i))
		{
			my_mlx_pixel_put(game->img2, ((game->player->x / 64) * tile_x)
				+ cos(angle) * (i / 64) * tile_x, ((game->player->y / 64)
					* tile_y) + sin(angle) * (i / 64) * tile_y, 0xFFBE6A);
			i++;
		}
		angle += game->player->fangle / WIDTH;
		j++;
	}
}

void	use_mouse(t_game *game)
{
	int	dx;

	if (game->mouse_flag == 1)
	{
		mlx_mouse_get_pos(game->mlx, game->win, &game->player->mouse_x,
			&game->player->mouse_y);
		dx = game->player->mouse_x - WIDTH / 2;
		if (game->player->mouse_x >= 0 && game->player->mouse_x <= WIDTH)
			game->player->player_angle += dx * MOUSE_SENSITIVITY;
		if ((game->player->player_angle >= PI / 2
				&& game->player->player_angle <= PI)
			|| (game->player->player_angle >= 3 * PI / 2
				&& game->player->player_angle <= 2 * PI))
		{
			game->player->horizslid = 1;
		}
		if ((game->player->player_angle > PI && game->player->player_angle < 3
				* PI / 2) || (game->player->player_angle > 0
				&& game->player->player_angle < PI / 2))
		{
			game->player->horizslid = -1;
		}
		mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
		mlx_mouse_hide(game->mlx, game->win);
	}
}

int	there_is_a_door(t_game *game, float x, float y)
{
	if (floor(y - 0.5) / TILE >= 0 && game->map2[(int)floor((y - 0.5)
				/ TILE)][(int)(x / TILE)] == 'D' && game->door == 0)
		return (2);
	if (floor(y + 0.5) / TILE >= game->my && game->map2[(int)floor((y + 0.5)
				/ TILE)][(int)(x / TILE)] == 'D' && game->door == 0)
		return (2);
	if (floor(x - 0.5) / TILE >= 0 && game->map2[(int)floor(y / TILE)][(int)((x
			- 0.5) / TILE)] == 'D' && game->door == 0)
		return (2);
	if (floor(x + 0.5) / TILE >= game->mx && game->map2[(int)floor(y
				/ TILE)][(int)((x + 0.5) / TILE)] == 'D' && game->door == 0)
		return (2);
	return (0);
}

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	tile_x;
	int	tile_y;
	int	j;

	i = 0;
	tile_x = WIDTH / 2 / game->mx;
	tile_y = HEIGHT / 2 / game->my;
	if (tile_x > 7)
		tile_x = 7;
	if (tile_y > 7)
		tile_y = 7;
	if (game->mx * tile_x > WIDTH / 2)
		tile_x = tile_y;
	if (game->my * tile_y > HEIGHT / 2)
		tile_y = tile_x;
	while (i < tile_x)
	{
		j = 0;
		while (j < tile_y)
		{
			my_mlx_pixel_put(game->img2, x * tile_x + i, y * tile_y + j, color);
			j++;
		}
		i++;
	}
}

void	render_2map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map2[y])
	{
		x = 0;
		while (game->map2[y][x])
		{
			if (game->map2[y][x] == '1')
			{
				draw_square(game, x, y, 0x808080);
			}
			if (ft_strchr("NSEW0", game->map2[y][x]))
			{
				draw_square(game, x, y, 0x82bc0000);
			}
			x++;
		}
		y++;
	}
}
