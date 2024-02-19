/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initgame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabou-rk <rabou-rk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:41:08 by rabou-rk          #+#    #+#             */
/*   Updated: 2024/02/19 01:27:56 by rabou-rk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
	player->movespeed = 1.5;
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
	move_player(game, player_x, player_y);
	move_to_sides(game, sidestep);
}

void	launch_game(t_info *info, t_game *game, t_player *player, t_img *img)
{
	cutmap2(info, game);
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
