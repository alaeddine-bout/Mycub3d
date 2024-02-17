/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initgame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabou-rk <rabou-rk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:41:08 by rabou-rk          #+#    #+#             */
/*   Updated: 2024/02/17 21:04:41 by rabou-rk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "cub.h"
#include <math.h>

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (y >= HEIGHT || x >= WIDTH || y <= 0 || x <= 0)
		return ;
	dst = data->addr + (y * data->linelength + x * (data->bitspixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	tile_x;
	int	tile_y;
	int	j;

	i = 0;
	tile_x = WIDTH / 2 / game->mx;
	tile_y = HEIGHT / 2 / game->my;
	if (tile_x > 7)
		tile_x = 7;
	if (tile_y > 7)
		tile_y = 7;
	if (game->mx * tile_x > WIDTH / 2)
		tile_x = tile_y;
	if (game->my * tile_y > HEIGHT / 2)
		tile_y = tile_x;
	while (i < tile_x)
	{
		j = 0;
		while (j < tile_y)
		{
			my_mlx_pixel_put(game->img2, x * tile_x + i, y * tile_y + j, color);
			j++;
		}
		i++;
	}
}

void	render_2map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map2[y])
	{
		x = 0;
		while (game->map2[y][x])
		{
			if (game->map2[y][x] == '1')
			{
				draw_square(game, x, y, 0x808080);
			}
			if (ft_strchr("NSEW0", game->map2[y][x]))
			{
				draw_square(game, x, y, 0x82bc0000);
			}
			x++;
		}
		y++;
	}
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

void	get_player_pos(t_game *game, t_player *player)
{
	int	y;
	int	x;

	y = 0;
	while (game->map2[y])
	{
		x = 0;
		while (game->map2[y][x] && game->map2[y][x] != '\n')
		{
			if (ft_strchr("NSEW", game->map2[y][x]))
			{
				player->y = ((y+ 1) * TILE) - (TILE / 2);
				player->x = ((x + 1)* TILE) - (TILE / 2);
				player->player = game->map2[y][x];
			}
			x++;
		}
		y++;
	}
}

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

void	init_player(t_game *game, t_player *player)
{
	get_player_pos(game, player);
	map_size(game);
	player->forwardmove = 0;
	player->sidemove = 0;
	player->rotation_move = 0;
	if (player->player == 'E')
		player->player_angle = 0;
	if (player->player == 'S')
		player->player_angle = PI / 2;
	if (player->player == 'W')
		player->player_angle = PI;
	if (player->player == 'N')
		player->player_angle = 3 * PI / 2;
	player->rotation_speed = 2 * (PI / 180) * 0.8;
	player->movespeed = 1.5;
}

int	there_is_a_wall2(t_game *game, float x, float y)
{
	if (x < 0 || y < 0 || x > WIDTH * TILE || y > HEIGHT * TILE)
		return (1);
	if ((y - 0.5) / TILE  >= 0 && game->map2[(int)floor((y - 0.5) / TILE)][(int)(x / TILE)] == '1')
		return (1);
	if ((y + 0.5) / TILE <= game->my&& game->map2[(int)floor((y + 0.5) / TILE)][(int)(x / TILE)] == '1')
		return (1);
	if ((x - 0.5) / TILE >= 0 && game->map2[(int)(y / TILE)][(int)((x - 0.5) / TILE)] == '1')
		return (1);
	if ((x + 0.5) / TILE <= game->mx && game->map2[(int)floor(y / TILE)][(int)((x + 0.5) / TILE)] == '1')
		return (1);
	return (0);
}

float	normalize_angle(float ray_angle)
{
	ray_angle = remainder(ray_angle, PI * 2);
	if (ray_angle < 0)
	{
		ray_angle = PI * 2 + ray_angle;
	}
	return (ray_angle);
}

void	init_val_3d(t_game *game, double i)
{
	game->wall_hit_x = (game->player->x + cos(game->angle) * i);
	game->wall_hit_y = (game->player->y + sin(game->angle) * i);
	if (round(fmod(round(game->wall_hit_x), TILE)) == 0
		&& round(fmod(round(game->wall_hit_y), TILE)) != 0)
	{
		game->vert = 0;
	}
	if (round(fmod(round(game->wall_hit_y), TILE)) == 0
		&& round(fmod(round(game->wall_hit_x), TILE)) != 0)
	{
		game->vert = 1;
	}
	game->distance = sqrt(pow(game->wall_hit_x - game->player->x, 2)
			+ pow(game->wall_hit_y - game->player->y, 2));
	if (game->wall_hit_x == game->player->x
		&& game->wall_hit_y == game->player->y)
		game->distance = sqrt(pow(game->wall_hit_x - game->player->x, 2)
				+ pow(game->wall_hit_y - 0.5 - game->player->y, 2));
	if (game->wall_hit_x == game->player->x
		&& game->wall_hit_y != game->player->y)
		game->distance = sqrt(pow(game->wall_hit_x - 0.5 - game->player->x, 2)
				+ pow(game->wall_hit_y - game->player->y, 2));
	if (game->wall_hit_x != game->player->x
		&& game->wall_hit_y == game->player->y)
		game->distance = sqrt(pow(game->wall_hit_x - game->player->x, 2)
				+ pow(game->wall_hit_y - 0.5 - game->player->y, 2));
	game->player->pro_wall_h = ((TILE / (game->distance * cos(game->angle
						- game->player->player_angle))) * ((WIDTH / 2)
				/ tan(FANGLE / 2)));
	game->player->top_pixel = (HEIGHT / 2) - (game->player->pro_wall_h / 2);
	if (game->player->top_pixel < 0)
		game->player->top_pixel = 0;
	game->player->bottom_pixel = (HEIGHT / 2) + (game->player->pro_wall_h / 2);
	if (game->player->bottom_pixel > HEIGHT)
	{
		game->player->bottom_pixel = HEIGHT;
	}
}

int get_xpm_color(t_game *game, void *texture, int x, int y, double wall_height)
{
    char *texture_addr;
    int bits_per_pixel;
    int size_line;
    int endian;

    texture_addr = mlx_get_data_addr(texture, &bits_per_pixel, &size_line, &endian);
    int base_color = *(int *)(texture_addr + ((int)(y * (TILE / wall_height)) * size_line + (x % TILE) * (bits_per_pixel / 8)));
    double darkness_factor = 1.0 - (game->distance / 550);
    int red = (base_color >> 16) & 0xFF;
    int green = (base_color >> 8) & 0xFF;
    int blue = base_color & 0xFF;
    red = (int)(red * darkness_factor);
    green = (int)(green * darkness_factor);
    blue = (int)(blue * darkness_factor);
    int darkened_color = (red << 16) | (green << 8) | blue;

    return darkened_color;
}

void	render_3d_game(t_game *game, int j, float i)
{
	long	l;
	long	end;
	float fac;

	l = 0;
	init_val_3d(game, i);
	l = 0;
	fac = HEIGHT /2;
	while (l < game->player->top_pixel)
	{
		int red = (game->c_rgb >> 16) & 0xFF;
		int green = (game->c_rgb >> 8) & 0xFF;
		int blue = game->c_rgb & 0xFF;

		// Decrease the intensity of each color channel
		red = (int)(red * (1.0 + fac / HEIGHT /2));
		green = (int)(green *(1.0 + fac /HEIGHT /2));
		blue = (int)(blue *(1.0 + fac / HEIGHT /2));

		// Combine the updated color channels into a new color value
		int darkened_color = (red << 16) | (green << 8) | blue;
		// printf("color === %d\n", darkened_color);
		// Set the pixel with the darkened color
		my_mlx_pixel_put(game->img2, j, l, darkened_color);
		fac -= 6;
		l++;
	}
	l = 2 * HEIGHT / 3;
	fac =  HEIGHT;
	while (l < HEIGHT)
	{
		// Extract the individual color channels from game->f_rgb
		int red = (game->f_rgb >> 16) & 0xFF;
		int green = (game->f_rgb >> 8) & 0xFF;
		int blue = game->f_rgb & 0xFF;

		// Decrease the intensity of each color channel
		red = (int)(red * (1.0 - fac / HEIGHT /1.02));
		green = (int)(green *(1.0 - fac / HEIGHT /1.02));
		blue = (int)(blue *(1.0 - fac / HEIGHT /1.02));

		// Combine the updated color channels into a new color value
		int darkened_color = (red << 16) | (green << 8) | blue;
		// printf("color === %d\n", darkened_color);
		// Set the pixel with the darkened color
		my_mlx_pixel_put(game->img2, j, l, darkened_color);
		fac -= 3;
		l++;
	}
	l = game->player->top_pixel;
	end = game->player->bottom_pixel;
	while (l < end)
	{
		if ((game->map2[(int)((game->wall_hit_y + 1)
					/ TILE)][(int)(game->wall_hit_x / TILE)] != '1'
				&& game->vert == 1))
			my_mlx_pixel_put(game->img2, j, l, get_xpm_color(game, game->north,
					game->wall_hit_x, l + (game->player->pro_wall_h) / 2
					- (HEIGHT / 2), game->player->pro_wall_h));
		if (game->map2[(int)(game->wall_hit_y / TILE)][(int)((game->wall_hit_x
					+ 1) / TILE)] != '1' && game->vert == 0)
			my_mlx_pixel_put(game->img2, j, l, get_xpm_color(game, game->west,
					game->wall_hit_y, l + (game->player->pro_wall_h) / 2
					- (HEIGHT / 2), game->player->pro_wall_h));
		if (game->map2[(int)(game->wall_hit_y / TILE)][(int)((game->wall_hit_x
					- 1) / TILE)] != '1' && game->vert == 0)
			my_mlx_pixel_put(game->img2, j, l, get_xpm_color(game, game->east,
					game->wall_hit_y, l + (game->player->pro_wall_h) / 2
					- (HEIGHT / 2), game->player->pro_wall_h));
		if (game->map2[(int)((game->wall_hit_y - 1)
				/ TILE)][(int)(game->wall_hit_x / TILE)] != '1'
			&& game->vert == 1)
			my_mlx_pixel_put(game->img2, j, l, get_xpm_color(game, game->south,
					game->wall_hit_x, l + (game->player->pro_wall_h) / 2
					- (HEIGHT / 2), game->player->pro_wall_h));
		l++;
	}
}

void	drawplayer(t_game *game)
{
	int	i;
	int	j;
	int	tile_x;
	int	tile_y;

	tile_x = WIDTH / 2 / game->mx;
	tile_y = HEIGHT / 2 / game->my;
	if (tile_x > 7)
		tile_x = 7;
	if (tile_y > 7)
		tile_y = 7;
	i = -1;
	if (game->flag == 1)
	{
		while (i < 1)
		{
			j = -1;
			while (j < 2)
			{
				my_mlx_pixel_put(game->img2, ((game->player->x / 64) * tile_x)
					+ i, (game->player->y / 64) * tile_y + j, 0x0FF000);
				j++;
			}
			i++;
		}
	}
}

void	raycasting(t_game *game)
{
	int		j;
	double	i;

	j = 0;
	game->angle = game->player->player_angle - (FANGLE / 2);
	while (j < WIDTH)
	{
		i = 0;
		while (i < 550 && !there_is_a_wall2(game, game->player->x + cos(game->angle) * i,
				game->player->y + sin(game->angle) * i))
			i += 1;
		render_3d_game(game, j, i);
		game->angle += FANGLE / WIDTH;
		j++;
	}
}

int	key_press(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	// printf("%f\n", game->player->player_angle);
	if (keycode == 65307)
		exit(1);
	if (keycode == 100)
		game->player->sidemove = 1;
	if (keycode == 97)
		game->player->sidemove = -1;
	if (keycode == 119)
		game->player->forwardmove = 1;
	if (keycode == 115)
		game->player->forwardmove = -1;
	if (keycode == 65363)
	{
		game->player->rotation_move = 1;
		game->player->horizslid = 1;
	}
	if (keycode == 65361)
	{
		game->player->rotation_move = -1;
		game->player->horizslid = -1;
	}
	if (keycode == 102)
		game->flag = 1;
	if (keycode == 114)
		game->flag = 0;
	return (0);
}

int	key_release(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == 65307)
		exit(1);
	if (keycode == 100)
		game->player->sidemove = 0;
	if (keycode == 97)
		game->player->sidemove = 0;
	if (keycode == 119)
		game->player->forwardmove = 0;
	else if (keycode == 115)
		game->player->forwardmove = 0;
	if (keycode == 65363)
		game->player->rotation_move = 0;
	else if (keycode == 65361)
		game->player->rotation_move = 0;
	return (0);
}

void	update(t_game *game)
{
	float	movestep;
	float	player_x;
	float	player_y;
	float	sidestep;

	mlx_mouse_get_pos(game->mlx, game->win, &game->player->mouse_x, &game->player->mouse_y);
	int dx = game->player->mouse_x - WIDTH / 2;
	if(game->player->mouse_x >= 0 && game->player->mouse_x <= WIDTH)
		game->player->player_angle += dx * MOUSE_SENSITIVITY;
	if (game->player->player_angle >= 2 * PI) {
        game->player->horizslid = 1;
    } else if (game->player->player_angle < 0) {
        game->player->horizslid = -1;
    }
    // Center the mouse position
    mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_hide(game->mlx, game->win);
	game->player->player_angle += game->player->rotation_move
		* game->player->rotation_speed;
	game->player->player_angle = normalize_angle(game->player->player_angle);
	movestep = game->player->forwardmove * game->player->movespeed;
	player_x = game->player->x + cos(game->player->player_angle) * movestep;
	player_y = game->player->y + sin(game->player->player_angle) * movestep;
	sidestep = game->player->sidemove * game->player->movespeed;
	if (!there_is_a_wall2(game, player_x, player_y))
	{
		// if (!there_is_a_wall2(game, player_x, game->player->y))
			game->player->x = player_x;
		// if (!there_is_a_wall2(game, game->player->x, player_y))
			game->player->y = player_y;
	}
	else
	{
		if (!there_is_a_wall2(game, game->player->x
				+ cos(game->player->player_angle + PI / 2) * movestep
				* game->player->horizslid, game->player->y))
			game->player->x = game->player->x + cos(game->player->player_angle
					+ PI / 2) * movestep * game->player->horizslid;
		if (!there_is_a_wall2(game, game->player->x, game->player->y
				+ sin(game->player->player_angle + PI / 2) * movestep
				* game->player->horizslid))
			game->player->y = game->player->y + sin(game->player->player_angle
					+ PI / 2) * movestep * game->player->horizslid;
	}
	if (!there_is_a_wall2(game, game->player->x + cos(game->player->player_angle
				+ PI / 2) * sidestep, game->player->y))
		game->player->x = game->player->x + cos(game->player->player_angle + PI
				/ 2) * sidestep;
	if (!there_is_a_wall2(game, game->player->x, game->player->y
			+ sin(game->player->player_angle + PI / 2) * sidestep))
		game->player->y = game->player->y + sin(game->player->player_angle + PI
				/ 2) * sidestep;
}

void	draw_rays(t_game *game)
{
	int		j;
	int		i;
	float	angle;
	int		tile_x;
	int		tile_y;

	j = 0;
	tile_x = WIDTH / 2 / game->mx;
	tile_y = HEIGHT / 2 / game->my;
	if (tile_x > 7)
		tile_x = 7;
	if (tile_y > 7)
		tile_y = 7;
	angle = normalize_angle(game->player->player_angle - (FANGLE / 2));
	while (j < WIDTH)
	{
		i = 0;
		while (i < 400 && !there_is_a_wall2(game, game->player->x + cos(angle)
				* i, game->player->y + sin(angle) * i))
		{
			my_mlx_pixel_put(game->img2, ((game->player->x / 64) * tile_x)
				+ cos(angle) * (i / 64) * tile_x, ((game->player->y / 64)
					* tile_y) + sin(angle) * (i / 64) * tile_y, 0xFFBE6A);
			i++;
		}
		angle += FANGLE / WIDTH;
		j++;
	}
}

int	render(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->img2->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img2->addr = mlx_get_data_addr(game->img2->img,
			&game->img2->bitspixel, &game->img2->linelength, &game->img2->end);
	game->img = game->img2;
	raycasting(game);
	if (game->flag == 1)
	{
		render_2map(game);
		drawplayer(game);
		draw_rays(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img2->img, 0, 0);
	mlx_destroy_image(game->mlx, game->img2->img);
	update(game);
	return (0);
}
void	assign_textures(t_info *info, t_game *game)
{
	int	texture_height;
	int	texture_width;

	game->north = mlx_xpm_file_to_image(game->mlx, info->north, &texture_width,
			&texture_height);
	if (!game->north)
		ft_error("Error: xpm file not found");
	game->south = mlx_xpm_file_to_image(game->mlx, info->south, &texture_width,
			&texture_height);
	if (!game->south)
		ft_error("Error: xpm file not found");
	game->west = mlx_xpm_file_to_image(game->mlx, info->west, &texture_width,
			&texture_height);
	if (!game->west)
		ft_error("Error: xpm file not found");
	game->east = mlx_xpm_file_to_image(game->mlx, info->east, &texture_width,
			&texture_height);
	if (!game->east)
		ft_error("Error: xpm file not found");
}
int int_to_rgb(int r, int g, int b) {
    return (r << 16) + (g << 8) + b;
}

void	rbg_converter(t_info *info, t_game *game)
{
	game->f_rgb = int_to_rgb(info->f_1.r, info->f_1.g, info->f_1.b);
	game->c_rgb = int_to_rgb(info->c_1.r, info->c_1.g, info->c_1.b);
}


void launch_game(t_info *info, t_game *game, t_player *player, t_img *img)
{
	cutmap2(info, game);
	rbg_converter(info, game);
	init_player(game, player);
	game->mlx = mlx_init();
	assign_textures(info, game);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	game->player = player;
	game->img2 = img;
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	printf("%f\n", game->player->player_angle);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
}
