/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maparse_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:42:55 by about             #+#    #+#             */
/*   Updated: 2024/02/19 05:02:12 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	check_map(char **map, int i, int *player)
{
	size_t	j;

	j = 0;
	while (map[i][j])
	{
		if (ft_strchr("NSWE", map[i][j]))
			(*player)++;
		if (ft_strchr("NSEW0D", map[i][j]))
		{
			if (map[i + 1] && j > ft_strlen(map[i + 1]))
				ft_error("\033[1;31mError: close map please!\033[0m");
			if (j <= ft_strlen(map[i]) - 1 && (!map[i - 1][j]
				|| !ft_strchr("NSEW01D", map[i - 1][j])))
				ft_error("\033[1;31mError: invalid map!\033[0m");
			if (!ft_strchr("NSEW01D", map[i + 1][j]))
				ft_error("\033[1;31mError: that shouldn't be there!\033[0m");
			if (!ft_strchr("NSEW0D1", map[i][j + 1]))
				ft_error("\033[1;31mError: Map not properly closed.\033[0m");
			if (j > 0 && !ft_strchr("NSEW01D", map[i][j - 1]))
				ft_error("\033[1;31mError: Unexpected elements in map.\033[0m");
		}
		j++;
	}
}

int	find_index(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] == '1')
			break ;
		i++;
	}
	return (i);
}

void	cutmaputil(t_info *info, int i)
{
	int	j;
	int	x;
	int	len;

	x = 0;
	while (info->map[i])
	{
		j = 0;
		len = ft_strlen(info->map[i]);
		info->map_2[x] = (char *)malloc(sizeof(char) * (len + 1));
		while (info->map[i][j])
		{
			info->map_2[x][j] = info->map[i][j];
			j++;
		}
		info->map_2[x][j] = '\0';
		i++;
		x++;
	}
	info->map_2[x] = NULL;
}

void	cutmap(t_info *info)
{
	int	i;
	int	x;

	i = find_index(info->map);
	x = 0;
	while (info->map[i])
	{
		i++;
		x++;
	}
	info->map_2 = (char **)malloc(sizeof(char *) * (x + 1));
	i = find_index(info->map);
	cutmaputil(info, i);
	last_line(info);
}

void	parse_map(t_info *info)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	while (info->map_2[i])
	{
		if (info->map_2[i][0] == '0' || info->map_2[i][0] == '\0')
			ft_error("\033[1;31mError: Errror: invalid map!\033[0m");
		if (i == 0)
			check_first(info->map_2[i]);
		else if (!info->map_2[i + 1])
			check_first(info->map_2[i]);
		else
			check_map(info->map_2, i, &player);
		if (info->map_2[i][ft_strlen(info->map_2[i])] == '0')
			ft_error("\033[1;31mError: invalid map!\033[0m");
		i++;
	}
	if (player != 1)
		ft_error("\033[1;31mError: There must be only one player\033[0m");
}
