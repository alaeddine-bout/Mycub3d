/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabou-rk <rabou-rk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:44:09 by about             #+#    #+#             */
/*   Updated: 2024/02/18 22:07:20 by rabou-rk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BONUS_H
# define CUB_BONUS_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>

# define TILE 64
# define WIDTH 840
# define HEIGHT 430
# define PI 3.1415926535
# define MOUSE_SENSITIVITY 0.003

typedef struct s_shadow
{
	char		*texture_addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			base_color;
	double		darkness_factor;
	int			red;
	int			green;
	int			blue;
	int			darkened_color;
}				t_shadow;

typedef struct s_player
{
	double		x;
	double		y;
	double		px;
	double		py;
	double		player_angle;
	int			sidemove;
	int			rotation_move;
	int			forwardmove;
	double		rotation_dir;
	double		movespeed;
	double		rotation_speed;
	long		pro_wall_h;
	long		top_pixel;
	long		bottom_pixel;
	int			horizslid;
	char		player;
	int			mouse_x;
	int			mouse_y;
	double		fangle;

}				t_player;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bitspixel;
	int			linelength;
	int			end;
}				t_img;

typedef struct s_game
{
	int			flag;
	void		*mlx;
	void		*win;
	void		*frame;
	void		*north;
	void		*south;
	void		*west;
	void		*east;
	void		*door_t;
	char		**map2;
	int			win_height;
	int			win_width;
	t_player	*player;
	t_img		*img;
	t_img		*img2;
	double		angle;
	double		distance;
	double		wall_hit_x;
	double		wall_hit_y;
	int			horiz;
	int			vert;
	int			mx;
	int			my;
	int			f_rgb;
	int			c_rgb;
	int			mouse_flag;
	int			door;
	int			door_flag;
}				t_game;

typedef struct s_colors
{
	int			r;
	int			g;
	int			b;
}				t_colors;

typedef struct s_info
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		**floor;
	char		**ceiling;
	char		**map;
	char		**map_2;
	int			found_no;
	int			found_so;
	int			found_we;
	int			found_ea;
	int			found_f;
	int			found_c;
	t_colors	f_1;
	t_colors	c_1;
}				t_info;

void			initial(t_info *info);
void			free_all(t_info *info, t_game *game);
void			double_free(char **line);
// parse textures
char			**readfile(char *file);
void			ft_error(char *error);
void			parse_textures(t_info *info);
char			*parse_path(char *line);
char			*remove_spaces(char *line);
int				parse_rgb(char **line, t_info *info, int flag);
void			check_spaces(char *line);
void			check_fill(char **line, int *r, int *g, int *b);
void			cubname(char *filename, char *name, char *error);
void			parse_colors_c(char *line, t_info *info, int *flag);
void			parse_colors_f(char *line, t_info *info, int *flag);
void			check_missing(t_info *info);
int				conditions(t_info *info, int j);
// parse map
int				find_index(char **map);
void			cutmap(t_info *info);
void			check_map(char **map, int i, int *player);
void			check_first(char *wall);
void			parse_map(t_info *info);
void			check_missing(t_info *info);
char			*parse_path(char *line);
void			assignthis(char **texture, char *line, int *flag);
// game graphics
void			launch_game(t_info *info, t_game *game, t_player *player,
					t_img *img);
void			draw_square(t_game *game, int x, int y, int color);
void			cutmap2(t_info *info, t_game *game);
;
void			get_player_pos(t_game *game, t_player *player);
void			drawplayer(t_game *game);
void			assign_textures(t_info *info, t_game *game);
int				get_xpm_color(t_game *game, void *texture, int x, int y);
void			draw_rays(t_game *game);
void			use_mouse(t_game *game);
int				there_is_a_door(t_game *game, float x, float y);
void			draw_square(t_game *game, int x, int y, int color);
void			render_2map(t_game *game);
float			normalize_angle(float ray_angle);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
int				there_is_a_wall(t_game *game, float x, float y);
void			move_player(t_game *game, float player_x, float player_y,
					float movestep);
void			move_to_sides(t_game *game, float sidestep);
int				key_release(int keycode, void *param);
int				key_press(int keycode, void *param);
void			key_press_norm(int keycode, t_game *game);
void			render_3d_game(t_game *game, int j, float i);
void			init_val_3d(t_game *game, double i);
void			raycasting(t_game *game);
int				there_is_a_wall(t_game *game, float x, float y);
float			normalize_angle(float ray_angle);
void			draw_ceiling(t_game *game, int j);
void			draw_floor(t_game *game, int j);
void			put_wall_textures(t_game *game, int j, long l);
void			assign_textures(t_info *info, t_game *game);
void			rbg_converter(t_info *info, t_game *game);
int				int_to_rgb(int r, int g, int b);
void			get_player_pos(t_game *game, t_player *player);
int				render(void *param);
void			render_3d_game(t_game *game, int j, float i);
void			draw_floor(t_game *game, int j);
void			draw_ceiling(t_game *game, int j);
void			put_wall_textures(t_game *game, int j, long l);
void			update(t_game *game);
void			cutmap2(t_info *info, t_game *game);
int				get_xpm_color(t_game *game, void *texture, int x, int y);
void			map_size(t_game *game);
int				linelen(char *str);
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif