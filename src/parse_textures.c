/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:26:07 by about             #+#    #+#             */
/*   Updated: 2024/02/16 15:44:34 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*parse_path(char *line)
{
	char	*path;
	int		len;

	path = ft_strdup(line + 3);
	len = ft_strlen(path);
	while (*path == ' ')
		path++;
	while (len > 0 && (path[len - 1] == ' ' || path[len - 1] == '\n'))
		path[--len] = '\0';
	cubname(path, ".xpm", "Error: textures must be in '.xpm' format");
	return (path);
}

void	check_missing(t_info *info)
{
	if (!info->north || !info->south || !info->west || !info->east)
		ft_error("Error: Missing texture path(s)");
	else if (!info->floor || !info->ceiling)
		ft_error("Error: Missing color");
}

void	assignthis(char **texture, char *line, int *flag)
{
	if (*flag)
		ft_error("Error: duplicated texture!");
	*texture = parse_path(line);
	*flag = 1;
}

int	conditions(t_info *info, int j)
{
	if (info->map[j][0] == 'N' && info->map[j][1] == 'O'
		&& info->map[j][2] == ' ')
		return (assignthis(&info->north, info->map[j], &info->found_no), 1);
	else if (info->map[j][0] == 'S' && info->map[j][1] == 'O'
		&& info->map[j][2] == ' ')
		return (assignthis(&info->south, info->map[j], &info->found_so), 1);
	else if (info->map[j][0] == 'W' && info->map[j][1] == 'E'
		&& info->map[j][2] == ' ')
		return (assignthis(&info->west, info->map[j], &info->found_we), 1);
	else if (info->map[j][0] == 'E' && info->map[j][1] == 'A'
		&& info->map[j][2] == ' ')
		return (assignthis(&info->east, info->map[j], &info->found_ea), 1);
	else if (info->map[j][0] == 'F' && info->map[j][1] == ' ')
		return (parse_colors_f(info->map[j], info, &info->found_f), 1);
	else if (info->map[j][0] == 'C' && info->map[j][1] == ' ')
		return (parse_colors_c(info->map[j], info, &info->found_c), 1);
	return (0);
}

void	parse_textures(t_info *info)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < 7)
	{
		if (!info->map[j])
			break ;
		info->map[j] = remove_spaces(info->map[j]);
		if (conditions(info, j))
			i++;
		j++;
	}
}
