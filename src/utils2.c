/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabou-rk <rabou-rk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:35:29 by rabou-rk          #+#    #+#             */
/*   Updated: 2024/02/18 21:54:04 by rabou-rk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void	cutmap2(t_info *info, t_game *game)
{
	int	i;
	int	x;
	int	j;
	int	len;

	i = find_index(info->map);
	x = 0;
	while (info->map[i])
	{
		i++;
		x++;
	}
	game->map2 = (char **)malloc(sizeof(char *) * (x + 1));
	i = find_index(info->map);
	x = 0;
	while (info->map[i])
	{
		j = 0;
		len = ft_strlen(info->map[i]);
		game->map2[x] = (char *)malloc(sizeof(char) * (len + 1));
		while (info->map[i][j])
		{
			game->map2[x][j] = info->map[i][j];
			j++;
		}
		game->map2[x][j] = '\0';
		i++;
		x++;
	}
	game->map2[x] = NULL;
}

int	get_xpm_color(t_game *game, void *texture, int x, int y)
{
	t_shadow	shadow;

	shadow.texture_addr = mlx_get_data_addr(texture, &shadow.bits_per_pixel,
			&shadow.size_line, &shadow.endian);
	shadow.base_color = *(int *)(shadow.texture_addr + ((int)(y * (TILE
						/ (double)game->player->pro_wall_h)) *shadow.size_line
				+ (x % TILE) * (shadow.bits_per_pixel / 8)));
	shadow.darkness_factor = 1.0 - (game->distance / 550);
	shadow.red = (shadow.base_color >> 16) & 0xFF;
	shadow.green = (shadow.base_color >> 8) & 0xFF;
	shadow.blue = shadow.base_color & 0xFF;
	shadow.red = (int)(shadow.red * shadow.darkness_factor);
	shadow.green = (int)(shadow.green * shadow.darkness_factor);
	shadow.blue = (int)(shadow.blue * shadow.darkness_factor);
	shadow.darkened_color = (shadow.red << 16)
		| (shadow.green << 8) | shadow.blue;
	return (shadow.darkened_color);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (y >= HEIGHT || x >= WIDTH || y <= 0 || x <= 0)
		return ;
	dst = data->addr + (y * data->linelength + x * (data->bitspixel / 8));
	*(unsigned int *)dst = color;
}

int	linelen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
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
