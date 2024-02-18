/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:26:22 by about             #+#    #+#             */
/*   Updated: 2024/02/18 23:55:19 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	parse_colors_f(char *line, t_info *info, int *flag)
{
	char	*temp;
	int		comma_count;

	temp = line + 2;
	comma_count = 0;
	while (*temp++)
	{
		if (*temp == ',')
		{
			comma_count++;
			if (comma_count > 2)
			{
				ft_error("\033[1;31mError: invalid floor color format\033[0m");
				return ;
			}
		}
	}
	if (*flag)
		ft_error("\033[1;31mError: duplicated floor color!\033[0m");
	info->floor = ft_split(line + 2, ',');
	if (parse_rgb(info->floor, info, 0) != 0)
		ft_error("\033[1;31mError : Invalid floor color\033[0m");
	*flag = 1;
	return ;
}

void	parse_colors_c(char *line, t_info *info, int *flag)
{
	char	*temp;
	int		comma_count;

	temp = line + 2;
	comma_count = 0;
	while (*temp++)
	{
		if (*temp == ',')
		{
			comma_count++;
			if (comma_count > 2)
			{
				ft_error("\033[1;31mError: invalid floor color format\033[0m");
				return ;
			}
		}
	}
	if (*flag)
		ft_error("\033[1;31mError: duplicated ceiling color!\033[0m");
	info->ceiling = ft_split(line + 2, ',');
	if (parse_rgb(info->ceiling, info, 1) != 0)
		ft_error("\033[1;31mError : Invalid ceiling color\033[0m");
	*flag = 1;
	return ;
}

void	checkk_fill(char **line, t_info *info, int flag)
{
	if (flag == 0)
		check_fill(line, &info->f_1.r, &info->f_1.g, &info->f_1.b);
	else
		check_fill(line, &info->c_1.r, &info->c_1.g, &info->c_1.b);
}

int	parse_rgb(char **line, t_info *info, int flag)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		j = 0;
		check_spaces(line[i]);
		while (line[i][j])
		{
			if (!ft_isdigit(line[i][j]) && (line[i][j] != ' '
				&& line[i][j] != '\n'))
			{
				ft_error("\033[1;31mError : invalid color format!\033[0m");
				return (1);
			}
			if (!line[i][j])
				break ;
			j++;
		}
		i++;
	}
	checkk_fill(line, info, flag);
	return (0);
}

void	check_num(char **line)
{
	int	i;
	int	j;

	j = 0;
	while (line[j])
	{
		i = 0;
		while (line[j][i] == ' ')
			i++;
		if (line[j][i] == '\n' || !line[j][i] || line[j] == NULL)
			ft_error("\033[1;31mError: Empty color\033[0m");
		j++;
	}
}
