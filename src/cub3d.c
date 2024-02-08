/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:39:34 by about             #+#    #+#             */
/*   Updated: 2024/02/08 15:07:32 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int ac, char **av)
{
	t_info		info;
	t_game		game;
	t_player	player;
	t_img		img;
	
	if (ac != 2)
		ft_error("Error: Wrong number of arguments");
	info.map = readfile(av[1]);
	if (!info.map)
		ft_error("Empty file!");
	(initial(&info), parse_textures(&info), check_missing(&info) );
	parse_map(&info);
	launch_game(&info, &game, &player, &img);
	free_all(&info, &game);
	return (0);
}
