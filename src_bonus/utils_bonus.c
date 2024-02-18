/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:28:19 by about             #+#    #+#             */
/*   Updated: 2024/02/19 00:05:55 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	ft_error(char *error)
{
	ft_putendl_fd(error, 2);
	exit(1);
}

void	free_all(t_info *info, t_game *game)
{
	free(info->north);
	free(info->south);
	free(info->east);
	free(info->west);
	double_free(info->floor);
	double_free(info->ceiling);
	double_free(info->map_2);
	double_free(game->map2);
}

void	double_free(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		free(line[i++]);
	free(line);
}

void	initial(t_info *info)
{
	info->west = NULL;
	info->south = NULL;
	info->north = NULL;
	info->east = NULL;
	info->ceiling = 0;
	info->floor = 0;
	info->f_1.r = 0;
	info->f_1.g = 0;
	info->f_1.b = 0;
	info->c_1.r = 0;
	info->c_1.g = 0;
	info->c_1.b = 0;
	info->found_no = 0;
	info->found_so = 0;
	info->found_we = 0;
	info->found_ea = 0;
	info->found_f = 0;
	info->found_c = 0;
}

void	check_spaces(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (j == 0 && ft_isdigit(line[i]))
			j = 1;
		if (j == 1 && (line[i] == ' ' || line[i] == '\t'))
		{
			if (line[i + 1] && ft_isdigit(line[i + 1]))
				ft_error("\033[1;35mError: ivalid color format!\033[0m");
		}
		i++;
	}
}
