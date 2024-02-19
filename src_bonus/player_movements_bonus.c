/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabou-rk <rabou-rk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:06:26 by rabou-rk          #+#    #+#             */
/*   Updated: 2024/02/19 02:28:29 by rabou-rk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub_bonus.h"

void	key_press_norm(int keycode, t_game *game)
{
	if (keycode == 65307)
		ft_error("\033[1;35mGAME OVER.\033[0m");
	if (keycode == 65362 && game->map2[(int)game->player->y
			/ TILE][(int)game->player->x / TILE] != 'D')
		game->door = 1;
	if (keycode == 65364 && game->map2[(int)game->player->y
			/ TILE][(int)game->player->x / TILE] != 'D')
		game->door = 0;
	if (keycode == 65289)
		game->flag = 1;
	if (keycode == 113)
		game->flag = 0;
	if (keycode == 65421)
		game->mouse_flag = 1;
	if (keycode == 65439)
		game->mouse_flag = 0;
}

int	key_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == 100)
		game->player->sidemove = 1;
	if (keycode == 97)
		game->player->sidemove = -1;
	if (keycode == 119)
		game->player->forwardmove = 1;
	if (keycode == 115)
		game->player->forwardmove = -1;
	if (keycode == 65363)
	{
		game->player->rotation_move = 1;
		game->player->horizslid = 1;
	}
	if (keycode == 65361)
	{
		game->player->rotation_move = -1;
		game->player->horizslid = -1;
	}
	key_press_norm(keycode, game);
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == 100)
		game->player->sidemove = 0;
	if (keycode == 97)
		game->player->sidemove = 0;
	if (keycode == 119)
		game->player->forwardmove = 0;
	else if (keycode == 115)
		game->player->forwardmove = 0;
	if (keycode == 65363)
		game->player->rotation_move = 0;
	else if (keycode == 65361)
		game->player->rotation_move = 0;
	return (0);
}

void	move_to_sides(t_game *game, float sidestep)
{
	if (!there_is_a_wall(game, game->player->x + cos(game->player->player_angle
				+ PI / 2) * sidestep, game->player->y))
		game->player->x = game->player->x + cos(game->player->player_angle + PI
				/ 2) * sidestep;
	if (!there_is_a_wall(game, game->player->x, game->player->y
			+ sin(game->player->player_angle + PI / 2) * sidestep))
		game->player->y = game->player->y + sin(game->player->player_angle + PI
				/ 2) * sidestep;
}

void	move_player(t_game *game, float player_x, float player_y,
		float movestep)
{
	if (!there_is_a_wall(game, player_x, player_y))
	{
		game->player->x = player_x;
		game->player->y = player_y;
	}
	else
	{
		if (!there_is_a_wall(game, game->player->x
				+ cos(game->player->player_angle + PI / 2) * movestep
				* game->player->horizslid, game->player->y))
			game->player->x = game->player->x + cos(game->player->player_angle
					+ PI / 2) * movestep * game->player->horizslid;
		if (!there_is_a_wall(game, game->player->x, game->player->y
				+ sin(game->player->player_angle + PI / 2) * movestep
				* game->player->horizslid))
			game->player->y = game->player->y + sin(game->player->player_angle
					+ PI / 2) * movestep * game->player->horizslid;
	}
}
