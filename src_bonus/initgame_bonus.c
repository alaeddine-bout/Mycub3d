/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initgame_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:41:08 by rabou-rk          #+#    #+#             */
/*   Updated: 2024/02/19 05:30:52 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	ft_exit(t_game *game)
{
	(void) game;
	ft_error("\033[1;35mGAME OVER.\033[0m");
	return (1);
}

void	init_player(t_game *game, t_player *player)
{
	get_player_pos(game, player);
	map_size(game);
	game->door = 0;
	player->horizslid = 1;
	player->fangle = 60 * (PI / 180);
	player->forwardmove = 0;
	player->sidemove = 0;
	player->rotation_move = 0;
	if (player->player == 'E')
		player->player_angle = 0;
	if (player->player == 'S')
		player->player_angle = PI / 2;
	if (player->player == 'W')
		player->player_angle = PI;
	if (player->player == 'N')
		player->player_angle = 3 * PI / 2;
	player->rotation_speed = 2 * (PI / 180) * 0.8;
	player->movespeed = 3;
}

void	drawplayer(t_game *game)
{
	int	i;
	int	j;
	int	tile_x;
	int	tile_y;

	tile_x = WIDTH / 2 / game->mx;
	tile_y = HEIGHT / 2 / game->my;
	if (tile_x > 7)
		tile_x = 7;
	if (tile_y > 7)
		tile_y = 7;
	i = -1;
	while (i < 1)
	{
		j = -1;
		while (j < 2)
		{
			my_mlx_pixel_put(game->img2, ((game->player->x / 64) * tile_x) + i,
				(game->player->y / 64) * tile_y + j, 0x0FF000);
			j++;
		}
		i++;
	}
}

void	update(t_game *game)
{
	float	movestep;
	float	player_x;
	float	player_y;
	float	sidestep;

	game->player->player_angle += game->player->rotation_move
		* game->player->rotation_speed;
	game->player->player_angle = normalize_angle(game->player->player_angle);
	movestep = game->player->forwardmove * game->player->movespeed;
	player_x = game->player->x + cos(game->player->player_angle) * movestep;
	player_y = game->player->y + sin(game->player->player_angle) * movestep;
	sidestep = game->player->sidemove * game->player->movespeed;
	move_player(game, player_x, player_y, movestep);
	move_to_sides(game, sidestep);
	use_mouse(game);
}

void	launch_game(t_info *info, t_game *game, t_player *player, t_img *img)
{
	rbg_converter(info, game);
	init_player(game, player);
	game->mlx = mlx_init();
	assign_textures(info, game);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	game->player = player;
	game->img2 = img;
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, ft_exit, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
}
