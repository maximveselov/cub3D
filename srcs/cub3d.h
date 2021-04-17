/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:31:29 by aannett           #+#    #+#             */
/*   Updated: 2021/04/16 15:31:32 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# define UDIV 1
# define VDIV 1
# define VMOVE 0.0
# define KEYPRESS	2
# define KEYRELEASE	3
# define KEYEXIT	17
# define TEX_W 64
# define TEX_H 64
# define ESC 53
# define A 0
# define D 2
# define S 1
# define W 13

typedef struct s_conf
{
	int					s_width;
	int					s_height;
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	char				*sp;
	char				dir;
	int					n_sp;
	int					floor;
	int					ceil;
	char				**map;
	char				**pmap;
	int					msize;
	int					mheight;
	double				**sprites;
	int					mwidth;
	int					**imap;
}						t_conf;
typedef struct s_mlx
{
	void				*ptr;
	void				*win;
	int					height;
	int					width;
	int					lheight;
	int					dstart;
	int					dend;
	double				mspeed;
	double				rspeed;
	int					**buf;
	int					**tex;
	double				*buf_z;
	int					*sprord;
	double				*sprdist;
}						t_mlx;
typedef struct s_img
{
	void				*image;
	int					*data;
	int					line_length;
	int					bpp;
	int					endian;
	int					width;
	int					height;
}						t_img;
typedef struct s_plr
{
	double				x;
	double				y;
	double				dir_x;
	double				dir_y;
	double				ray_x;
	double				ray_y;
	double				plane_x;
	double				plane_y;
	double				camera_x;
	int					map_x;
	int					map_y;
	double				sdist_x;
	double				sdist_y;
	double				ddist_x;
	double				ddist_y;
	double				pwdist;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
	double				wall_x;
	int					tex_x;
	int					tex_y;
	double				step;
	double				tex_pos;
	int					color;
}						t_plr;
typedef struct s_spr
{
	double				first;
	int					second;
}						t_spr;
typedef struct s_sprite
{
	double				x;
	double				y;
	double				inv_det;
	double				trans_x;
	double				trans_y;
	int					v_move_screen;
	int					screen_x;
	int					height;
	int					d_start_y;
	int					d_end_y;
	int					width;
	int					d_start_x;
	int					d_end_x;
}						t_sprite;
typedef struct s_pair
{
	double				first;
	int					second;
}						t_pair;
typedef struct s_ptr
{
	t_conf				conf;
	t_mlx				mlx;
	t_plr				plr;
	t_sprite			sprite;
}						t_ptr;
typedef struct s_main
{
	double				x;
	double				y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	void				*mlx;
	void				*win;
	int					a;
	int					w;
	int					s;
	int					d;
	int					esc;
	int					**buf;
	double				*buf_z;
	int					**texture;
	double				mspeed;
	double				rspeed;
	int					*sprord;
	double				*sprdist;
	int					**map;
	t_ptr				ptr;
	t_img				img;
}						t_main;
void					parse_conf(t_ptr *ptr, char *file);
t_ptr					init_ptr(void);
t_mlx					init_mlx(t_ptr *ptr);
void					exit_error_ptr(t_ptr *ptr, char *error);
int						create_trgb(int t, int r, int g, int b);
void					update_key(t_main *main);
void					clear_list(t_list **head);
void					clear_map(char **map);
void					free_ptr(t_ptr *ptr);
int						exit_normal(t_main *main);
void					exit_error_main(t_main *main, char *error);
void					sort_order(t_pair *ords, int amount);
void					sprite_sort(int *ord, double *dist, int n);
void					calc_dir(t_main *main, t_ptr *ptr, int x);
void					calc_step(t_main *main, t_ptr *ptr);
void					dda(t_main *main, t_ptr *ptr);
void					calc_drawline(t_main *main, t_ptr *ptr);
void					cast_floor(t_main *main, const t_ptr *ptr);
int						get_right_tex(t_ptr *ptr);
void					calc_tex(t_main *main, t_ptr *ptr);
void					draw_tex_line(t_main *main, t_ptr *ptr, int x,
							int tex_n);
void					cast_walls(t_main *main, t_ptr *ptr);
void					sprite_matrix(t_ptr *ptr, int i, t_main *main);
void					sprite_drawline(t_ptr *ptr);
void					fill_sprite_buf(t_main *main, t_ptr *ptr, int stripe,
							int tex_x);
void					draw_sprite(t_main *main, t_ptr *ptr);
void					cast_sprites(t_ptr *ptr, t_main *main);
void					draw(t_main *main, t_ptr *ptr);
void					calc(t_main *main, t_ptr *ptr);
int						main_loop(t_main *main);
void					rotate_keys_utils(t_main *main, double old_dir_x, double
							old_plane_x);
void					rotate_keys(t_main *main);
void					update_key(t_main *main);
int						key_press(int key, t_main *main);
int						key_release(int key, t_main *main);
void					load_image(t_main *main, int *texture, char *path,
							t_img *img);
void					load_texture(t_main *main, t_ptr *ptr);
void					fill_header(t_main *main, int file, int size);
void					draw_bmp(t_main *main, int file);
void					screenshot(t_main *main);
void					dir_utils(t_main *main, char c);
void					get_right_dir(t_main *main, char c);
void					init_sprite_arr(t_main *main, t_ptr *ptr);
void					init_buf(t_main *main, t_ptr *ptr);
void					init_tex_buf(t_main *main, t_ptr *ptr);
void					init_structs(char *argv, t_main *main, t_ptr *ptr);
void					parse_res(t_ptr *ptr);
void					fill_tex(char **dest, char *src, t_ptr *ptr);
void					parse_tex(t_ptr *ptr);
void					parse_rgb(char *src, int *dest, t_ptr *ptr);
void					parse_col(t_ptr *ptr);
void					check_map(t_ptr *ptr);
void					get_plr_info(t_ptr *ptr, int x, int y, char dir);
void					parse_coordinates(t_ptr *ptr);
double					*get_sprite_array(int x, int y);
void					parse_sprites(t_ptr *ptr);
int						count_sprites(char **map);
void					parse_int_map(t_ptr *ptr);
void					parse_map(t_ptr *ptr);
void					parse_params(t_ptr *ptr);
int						string_is_valid(char *str);
void					clear_list(t_list **head);
void					clear_map(char **map);
void					free_arr_double(double **arr, int size);
void					free_arr_int(int **arr, int size);
void					free_ptr(t_ptr *ptr);
int						check_file_format(char *file, char *format);
#endif
