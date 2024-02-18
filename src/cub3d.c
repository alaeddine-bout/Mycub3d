/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:39:34 by about             #+#    #+#             */
/*   Updated: 2024/02/18 23:14:37 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	int_to_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	rbg_converter(t_info *info, t_game *game)
{
	game->f_rgb = int_to_rgb(info->f_1.r, info->f_1.g, info->f_1.b);
	game->c_rgb = int_to_rgb(info->c_1.r, info->c_1.g, info->c_1.b);
}

void	assign_textures(t_info *info, t_game *game)
{
	int	texture_height;
	int	texture_width;

	game->north = mlx_xpm_file_to_image(game->mlx, info->north, &texture_width,
			&texture_height);
	if (!game->north)
		ft_error("\033[1;31mError: xpm file not found\033[0m");
	game->south = mlx_xpm_file_to_image(game->mlx, info->south, &texture_width,
			&texture_height);
	if (!game->south)
		ft_error("\033[1;31mError: xpm file not found\033[0m");
	game->west = mlx_xpm_file_to_image(game->mlx, info->west, &texture_width,
			&texture_height);
	if (!game->west)
		ft_error("\033[1;31mError: xpm file not found\033[0m");
	game->east = mlx_xpm_file_to_image(game->mlx, info->east, &texture_width,
			&texture_height);
	if (!game->east)
		ft_error("\033[1;31mError: xpm file not found\033[0m");
	game->door_t = mlx_xpm_file_to_image(game->mlx, "./textures/door.xpm",
			&texture_width, &texture_height);
	if (!game->door_t)
		ft_error("\033[1;31mError: xpm file not found\033[0m");
}

int	main(int ac, char **av)
{
	t_info		info;
	t_game		game;
	t_player	player;
	t_img		img;

	if (ac != 2)
		ft_error("\033[1;31mError: Wrong number of arguments\033[0m");
	info.map = readfile(av[1]);
	if (!info.map)
		ft_error("\033[1;31mEmpty file!\033[0m");
	(initial(&info), parse_textures(&info), check_missing(&info));
	parse_map(&info);
	launch_game(&info, &game, &player, &img);
	free_all(&info, &game);
	return (0);
}
