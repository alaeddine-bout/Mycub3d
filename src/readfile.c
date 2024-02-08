/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:02:45 by about             #+#    #+#             */
/*   Updated: 2024/02/08 16:52:04 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

void	check_first(char *wall)
{
	int	i;

	i = 0;
	while (wall[i])
	{
		if (wall[i] == '\n')
			break;
		if (wall[i] != '1' && wall[i] != ' ' && wall[i] != '\t')
			ft_error("Error: map should be closed by walls");
		i++;
	}
}

char	*remove_spaces(char *line)
{
	char	*modif;
	int		len;

	modif = ft_strdup(line);
	free(line);
	while (*modif && (*modif == ' ' || *modif == '\t'))
		modif++;
	len = ft_strlen(modif);
	if (len > 0 && (modif[len - 1] == ' ' || modif[len - 1] == '\t'))
		modif[--len] = '\0';
	return (modif);
}

void	cubname(char *filename, char *name, char *error)
{
	int len = ft_strlen(filename);

	if (len < 4 || strcmp(filename + len - 4, name) != 0)
		ft_error(error);
}

char	**readutils(char *file, int i)
{
	char	**mapped;
	int		fd;
	int		j;
	
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("Could not open file.");
	mapped = malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (j <= i)
		mapped[j++] = get_next_line(fd);
	close(fd);
	return (mapped);
}
char	**readfile(char *file)
{
	int		fd;
	int		i;
	char	**mapped;
	char	*tmp;

	cubname(file, ".cub", "Error: The filename must be in .cub format");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("Could not open file.");
	i = 0;
	while (1)
	{
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break;
		free(tmp);
		i++;
	}
	close(fd);
	mapped = readutils(file, i);
	return (mapped);
}
