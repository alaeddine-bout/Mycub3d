/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:26:22 by about             #+#    #+#             */
/*   Updated: 2024/02/08 16:23:44 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

void	parse_colors_f(char *line, t_info *info, int *flag)
{
	char *temp; 
	int comma_count; 
	
	temp = line + 2;
	comma_count = 0;
	while(*temp++)
	{
		if(*temp == ',')
		{
			comma_count++;
			if(comma_count > 2)
			{
				ft_error("Error: invalid floor color format");
				return;
			}
		}
	}
	if(*flag)
		ft_error("Error: duplicated floor color!");
	info->floor = ft_split(line + 2, ',');
	if (parse_rgb(info->floor, info, 0) != 0)
		ft_error("Error : Invalid floor color");
	*flag = 1;
	return ;	
}
void	parse_colors_c(char *line, t_info *info, int *flag)
{
	char *temp; 
	int comma_count;
 
	temp = line + 2;
	comma_count = 0;
	while(*temp++)
	{
		if(*temp == ',')
		{
			comma_count++;
			if(comma_count > 2)
			{
				ft_error("Error: invalid floor color format");
				return;
			}
		}
	}
	if(*flag)
		ft_error("Error: duplicated ceiling color!");
	info->ceiling = ft_split(line + 2 , ',');
	if (parse_rgb(info->ceiling, info, 1) != 0)
		ft_error("Error : Invalid ceiling color");
	*flag = 1;
	return ;
}
void	checkk_fill(char **line, t_info *info,int flag)
{
	if(flag == 0)
		check_fill(line, &info->f_1.r,  &info->f_1.g,  &info->f_1.b);
	else
		check_fill(line, &info->c_1.r,  &info->c_1.g,  &info->c_1.b);
}
int	parse_rgb(char **line, t_info *info, int flag)
{
	int i;
	int j;

	i = 0;
	while(line[i])
	{
		j = 0;
		check_spaces(line[i]);
		while(line[i][j])
		{
			if (!ft_isdigit(line[i][j]) && (line[i][j] != ' '
				&& line[i][j] != '\n'))
				return (ft_error("Error : invalid color format!"), 1);
			if(!line[i][j])
				break ;
			j++;
		}
		i++;
	}
	checkk_fill(line, info, flag);
	return (0);
}

void	check_fill(char **line, int *r ,int *g, int *b)
{
	*r = ft_atoi(line[0]);
	if(*r < 0 || *r > 255)
		ft_error("Error: invalid range");
	*g = ft_atoi(line[1]);;
	if(*g < 0 || *g > 255)
		ft_error("Error: invalid range");
	*b = ft_atoi(line[2]);
	if(*b < 0 || *b > 255)
		ft_error("Error: invalid range");
}