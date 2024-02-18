/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:51:59 by about             #+#    #+#             */
/*   Updated: 2024/02/18 23:53:19 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

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
		ft_error("\033[1;31mError: Invalid range\033[0m");
	*g = ft_atoi(line[1]);
	if (*g < 0 || *g > 255)
		ft_error("\033[1;31mError: Invalid range\033[0m");
	*b = ft_atoi(line[2]);
	if (*b < 0 || *b > 255)
		ft_error("\033[1;31mError: Invalid range\033[0m");
}
