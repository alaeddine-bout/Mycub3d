/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabou-rk <rabou-rk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:44:09 by about             #+#    #+#             */
/*   Updated: 2024/02/17 21:07:16 by rabou-rk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

# include <fcntl.h>
# include <math.h> 
# include <mlx.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

# define TILE 64
# define WIDTH 840
# define HEIGHT 430
# define PI 3.1415926535
# define FANGLE 60 * (PI / 180)
#define MOUSE_SENSITIVITY 0.001


typedef struct s_player {
	double		x;
	double		y;
	double	px;
	double	py;
	double	player_angle;
	int		sidemove;
	int		rotation_move;
	int		forwardmove;
	double	rotation_dir;
	double movespeed;
	double	rotation_speed;
	long pro_wall_h;
	long top_pixel;
	long	bottom_pixel;
	int horizslid;
	char player;
	int		mouse_x;
	int		mouse_y;
	
} t_player;


typedef struct s_img {
	void	*img;
	char	*addr;
	int		bitspixel;
	int		linelength;
	int		end;
}	t_img;

typedef struct s_game {
	int			flag;
	void		*mlx;
	void		*win;
	void		*frame;
	void		*north;
	void		*south;
	void		*west;
	void		*east;
	char		**map2;
	int 	win_height;
	int		win_width;
	t_player	*player;
	t_img *img;
	t_img *img2;
    double angle;
	double distance;
	double wall_hit_x;
	double wall_hit_y;
	int horiz;
	int vert;
	int		mx;
	int		my;
	int		f_rgb;
	int		c_rgb;
} t_game;

typedef struct s_colors {
	int	r;
	int	g;
	int	b;
} t_colors;


typedef struct s_info {
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
} t_info;

void	initial(t_info *info);
void	free_all(t_info *info, t_game *game);
void	double_free(char **line);
// parse textures
char    **readfile(char *file);
void    ft_error(char *error);
void	parse_textures(t_info *info);
char	*parse_path(char *line);
char	*remove_spaces(char *line);
int		parse_rgb(char **line, t_info *info, int flag);
void	check_spaces(char *line);
void	check_fill(char **line, int *r ,int *g, int *b);
void	cubname(char *filename, char *name, char *error);
void	parse_colors_c(char *line, t_info *info, int *flag);
void	parse_colors_f(char *line, t_info *info, int *flag);
void	check_missing(t_info *info);
int		conditions(t_info *info, int j);
// parse map
int		find_index(char **map);
void	cutmap(t_info *info);
void	check_map(char **map, int i, int *player);
void	check_first(char *wall);
void	parse_map(t_info *info);
void	check_missing(t_info *info);
char	*parse_path(char *line);
void	assignthis(char **texture, char *line, int *flag);
// game graphics
void    launch_game(t_info *info, t_game *game, t_player *player, t_img *img);
void    render_2dmap(t_game *game);
void	draw_square(t_game *game, int x, int y, int color);
void	cutmap2(t_info *info, t_game *game);;
void	get_player_pos(t_game *game, t_player *player);
void	drawplayer(t_game *game);
void	update_game(t_game *game);
void	draw_rotated(t_game *game, int x, int y, double angle);
void	assign_textures(t_info *info, t_game *game);
int		get_xpm_color(t_game *game, void *texture, int x, int y, double wall_height);

#endif