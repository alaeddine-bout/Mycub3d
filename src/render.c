/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabou-rk <rabou-rk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:24:35 by rabou-rk          #+#    #+#             */
/*   Updated: 2024/02/18 22:31:25 by rabou-rk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub.h"

void	put_wall_textures(t_game *game, int j, long l)
{
	if ((game->map2[(int)((game->wall_hit_y + 1) / TILE)][(int)(game->wall_hit_x
		/ TILE)] != '1' && game->vert == 1))
		my_mlx_pixel_put(game->img2, j, l, get_xpm_color(game, game->north,
				game->wall_hit_x, l + (game->player->pro_wall_h) / 2 - (HEIGHT
					/ 2)));
	if (game->map2[(int)(game->wall_hit_y / TILE)][(int)((game->wall_hit_x + 1)
			/ TILE)] != '1' && game->vert == 0)
		my_mlx_pixel_put(game->img2, j, l, get_xpm_color(game, game->west,
				game->wall_hit_y, l + (game->player->pro_wall_h) / 2 - (HEIGHT
					/ 2)));
	if (game->map2[(int)(game->wall_hit_y / TILE)][(int)((game->wall_hit_x - 1)
			/ TILE)] != '1' && game->vert == 0)
		my_mlx_pixel_put(game->img2, j, l, get_xpm_color(game, game->east,
				game->wall_hit_y, l + (game->player->pro_wall_h) / 2 - (HEIGHT
					/ 2)));
	if (game->map2[(int)((game->wall_hit_y - 1) / TILE)][(int)(game->wall_hit_x
			/ TILE)] != '1' && game->vert == 1)
		my_mlx_pixel_put(game->img2, j, l, get_xpm_color(game, game->south,
				game->wall_hit_x, l + (game->player->pro_wall_h) / 2 - (HEIGHT
					/ 2)));
}

void	draw_ceiling(t_game *game, int j)
{
	long		l;
	float		fac;
	t_shadow	shadow;

	l = 0;
	fac = HEIGHT / 2;
	while (l < game->player->top_pixel)
	{
		shadow.red = (game->c_rgb >> 16) & 0xFF;
		shadow.green = (game->c_rgb >> 8) & 0xFF;
		shadow.blue = game->c_rgb & 0xFF;
		shadow.red = (int)(shadow.red * (1.0 + fac / HEIGHT / 2));
		shadow.green = (int)(shadow.green * (1.0 + fac / HEIGHT / 2));
		shadow.blue = (int)(shadow.blue * (1.0 + fac / HEIGHT / 2));
		shadow.darkened_color = (shadow.red << 16) | (shadow.green << 8)
			| shadow.blue;
		my_mlx_pixel_put(game->img2, j, l, shadow.darkened_color);
		fac -= 6;
		l++;
	}
}

void	draw_floor(t_game *game, int j)
{
	long		l;
	float		fac;
	t_shadow	shadow;

	l = 2 * HEIGHT / 3;
	fac = HEIGHT;
	while (l < HEIGHT)
	{
		shadow.red = (game->f_rgb >> 16) & 0xFF;
		shadow.green = (game->f_rgb >> 8) & 0xFF;
		shadow.blue = game->f_rgb & 0xFF;
		shadow.red = (int)(shadow.red * (1.0 - fac / HEIGHT / 1.02));
		shadow.green = (int)(shadow.green * (1.0 - fac / HEIGHT / 1.02));
		shadow.blue = (int)(shadow.blue * (1.0 - fac / HEIGHT / 1.02));
		shadow.darkened_color = (shadow.red << 16) | (shadow.green << 8)
			| shadow.blue;
		my_mlx_pixel_put(game->img2, j, l, shadow.darkened_color);
		fac -= 3;
		l++;
	}
}

void	render_3d_game(t_game *game, int j, float i)
{
	long	l;
	long	end;

	init_val_3d(game, i);
	draw_ceiling(game, j);
	draw_floor(game, j);
	l = game->player->top_pixel;
	end = game->player->bottom_pixel;
	while (l < end)
	{
		put_wall_textures(game, j, l);
		l++;
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
	mlx_put_image_to_window(game->mlx, game->win, game->img2->img, 0, 0);
	mlx_destroy_image(game->mlx, game->img2->img);
	update(game);
	return (0);
}
