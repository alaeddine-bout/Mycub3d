/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 00:02:34 by about             #+#    #+#             */
/*   Updated: 2024/02/22 16:06:06 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	mini_tile(t_game *game, int *tile_x, int *tile_y)
{
	*tile_x = WIDTH / 2 / game->mx;
	*tile_y = HEIGHT / 2 / game->my;
	if (*tile_x > 7)
		*tile_x = 7;
	if (*tile_y > 7)
		*tile_y = 7;
}

void	map_size(t_game *game)
{
	int	y;

	y = 0;
	game->mx = linelen(game->map2[y]);
	while (game->map2[y] && game->map2[y][0] != '\n')
	{
		if (game->map2[y][0] != '\0' && game->mx < linelen(game->map2[y + 1]))
			game->mx = linelen(game->map2[y + 1]);
		y++;
	}
	game->my = y;
}

void	check_fill(char **line, int *r, int *g, int *b)
{
	check_num(line);
	*r = ft_atoi(line[0]);
	if (*r < 0 || *r > 255)
		ft_error("Error: invalid range");
	*g = ft_atoi(line[1]);
	if (*g < 0 || *g > 255)
		ft_error("Error: invalid range");
	*b = ft_atoi(line[2]);
	if (*b < 0 || *b > 255)
		ft_error("Error: invalid range");
}

void	last_line(t_info *info)
{
	int	i;

	i = 0;
	if(!info->map_2[i])
		ft_error("\033[1;31mError: empty map!\033[0m");
	while (info->map_2[i + 1])
		i++;
	if (info->map_2[i][0] != '1' && info->map_2[i][0] != ' ')
		ft_error("\033[1;31mError: map always has to be the last\033[0m");
}
