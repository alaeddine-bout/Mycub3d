/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabou-rk <rabou-rk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:10:22 by rabou-rk          #+#    #+#             */
/*   Updated: 2024/02/18 22:24:30 by rabou-rk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub_bonus.h"

void	get_player_pos(t_game *game, t_player *player)
{
	int	y;
	int	x;

	y = 0;
	while (game->map2[y])
	{
		x = 0;
		while (game->map2[y][x] && game->map2[y][x] != '\n')
		{
			if (ft_strchr("NSEW", game->map2[y][x]))
			{
				player->y = ((y + 1) * TILE) - (TILE / 2);
				player->x = ((x + 1) * TILE) - (TILE / 2);
				player->player = game->map2[y][x];
			}
			x++;
		}
		y++;
	}
}

float	normalize_angle(float ray_angle)
{
	ray_angle = remainder(ray_angle, PI * 2);
	if (ray_angle < 0)
	{
		ray_angle = PI * 2 + ray_angle;
	}
	return (ray_angle);
}

int	there_is_a_wall(t_game *game, float x, float y)
{
	if (x < 0 || y < 0 || x > WIDTH * TILE || y > HEIGHT * TILE)
		return (1);
	if (floor(y - 0.5) / TILE >= 0 && game->map2[(int)floor((y - 0.5)
				/ TILE)][(int)(x / TILE)] == '1')
		return (1);
	if (floor(y + 0.5) / TILE <= game->my && game->map2[(int)floor((y + 0.5)
				/ TILE)][(int)(x / TILE)] == '1')
		return (1);
	if (floor(x - 0.5) / TILE >= 0 && game->map2[(int)(y / TILE)][(int)floor((x
				- 0.5) / TILE)] == '1')
		return (1);
	if (floor(x + 0.5) / TILE <= game->mx && game->map2[(int)(y
			/ TILE)][(int)floor((x + 0.5) / TILE)] == '1')
		return (1);
	return (there_is_a_door(game, x, y));
}

void	raycasting(t_game *game)
{
	int		j;
	double	i;

	j = 0;
	game->angle = normalize_angle(game->player->player_angle
			- (game->player->fangle / 2));
	while (j < WIDTH)
	{
		i = 0;
		while (i < 550 && !there_is_a_wall(game, game->player->x
				+ cos(game->angle) * i, game->player->y + sin(game->angle) * i))
			i += 1;
		render_3d_game(game, j, i);
		game->angle += game->player->fangle / WIDTH;
		j++;
	}
}

void	init_val_3d(t_game *game, double i)
{
	game->wall_hit_x = (game->player->x + cos(game->angle) * i);
	game->wall_hit_y = (game->player->y + sin(game->angle) * i);
	if (round(fmod(round(game->wall_hit_x), TILE)) == 0
		&& round(fmod(round(game->wall_hit_y), TILE)) != 0)
		game->vert = 0;
	if (round(fmod(round(game->wall_hit_y), TILE)) == 0
		&& round(fmod(round(game->wall_hit_x), TILE)) != 0)
		game->vert = 1;
	game->distance = sqrt(pow(game->wall_hit_x - game->player->x, 2)
			+ pow(game->wall_hit_y - game->player->y, 2));
	game->player->pro_wall_h = ((TILE / (game->distance * cos(game->angle
						- game->player->player_angle))) * ((WIDTH / 2)
				/ tan(game->player->fangle / 2)));
	game->player->top_pixel = (HEIGHT / 2) - (game->player->pro_wall_h / 2);
	if (game->player->top_pixel < 0)
		game->player->top_pixel = 0;
	game->player->bottom_pixel = (HEIGHT / 2) + (game->player->pro_wall_h / 2);
	if (game->player->bottom_pixel > HEIGHT)
		game->player->bottom_pixel = HEIGHT;
}
