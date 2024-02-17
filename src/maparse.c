/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maparse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:42:55 by about             #+#    #+#             */
/*   Updated: 2024/02/16 15:49:06 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_map(char **map, int i, int *player)
{
	size_t	j;

	j = 0;
	while (map[i][j])
	{
		if (ft_strchr("NSWE", map[i][j]))
			(*player)++;
		if (ft_strchr("NSEW0", map[i][j]))
		{
			if (map[i + 1] && j > ft_strlen(map[i + 1]))
				ft_error("Error: close map please!");
			if (j <= ft_strlen(map[i]) - 1 && (!map[i - 1][j]
				|| !ft_strchr("NSEW01", map[i - 1][j])))
				ft_error("Error: invalid map!");
			if (!ft_strchr("NSEW01", map[i + 1][j]))
				ft_error("Error: that shouldn't be there!");
			if (!ft_strchr("NSEW01", map[i][j + 1]))
				ft_error("Error: map should be surrounded by walls");
			if (j > 0 && !ft_strchr("NSEW01", map[i][j - 1]))
				ft_error("Error: that shouldn't be there either");
		}
		j++;
	}
}

int	find_index(char **map)
{
	int	i;
	
	i = 0;
	while (map[i])
	{
		if (map[i][0] == '1')
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
}

void	parse_map(t_info *info)
{
	int	i;
	int	player;

	i = 0;
	player = 0;
	cutmap(info);
	while (info->map_2[i])
	{
		if (info->map_2[i][0] == '0' || info->map_2[i][0] == '\0')
			ft_error("Error: Errror: invalid map!");
		if (i == 0)
			check_first(info->map_2[i]);
		else if (!info->map_2[i + 1])
			check_first(info->map_2[i]);
		else
			check_map(info->map_2, i , &player);
		if (info->map_2[i][ft_strlen(info->map_2[i])] == '0')
			ft_error("Error: invalid map!");
		i++;
	}
	if (player != 1)
		ft_error("Error: There must be only one player");
}
