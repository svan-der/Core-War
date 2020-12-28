/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   corewar.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 19:16:12 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/17 23:59:59 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "op.h"
# include <ncurses.h>

# define FALSE 0
# define TRUE 1
# define MASK 3
# define OP_ZJMP 0x09

typedef struct			s_op
{
	char				name[8];
	char				n_arg;
	char				t_arg[3];
	int					id;
	int					n_cycle;
	char				description[64];
	char				encode;
	char				label_size;
}						t_op;

/*
** Struct to save and access the cursors information
*/

typedef struct			s_cursor
{
	int					decay;
	struct s_cursor		*next;
	struct s_op			op;
	int					registries[REG_NUMBER + 1];
	int					arg[3];
	int					pos;
	int					id;
	int					pid;
	int					carry;
	int					last_live;
	int					wait_cycles;
	int					jump;
}						t_cursor;

typedef struct			s_player
{
	struct s_player		*next;
	struct s_player		*prev;
	struct s_header		*data;
	char				*filename;
	unsigned char		code[CHAMP_MAX_SIZE + 1];
	int					id;
	int					rank_a;
	int					rank_n;
	int					pos;
}						t_player;

typedef struct			s_env
{
	struct s_player		*players;
	struct s_cursor		*cursors;
	struct s_arena		*arena;
	struct s_vis		*vis;
	char				*arena_color;
	char				**argv;
	int					cursors_count;
	int					argc;
	int					champ_count;
	int					champ_last_reported;
	int					flag_dump;
	int					cursor_total;
	int					cycles_total;
	int					cycles_counter;
	int					live_counter;
	int					cycles_to_die;
	int					cycles_since_check;
	int					checks_count;
	char				flag_a;
	char				flag_v;
}						t_env;

typedef enum			e_prgm_sig
{
	SUCCESS = 0,
	ERROR = -1,
	error_ctd_lte_zero = -2
}						t_prgm_sig;

typedef struct			s_arena
{
	unsigned char		*code;
	unsigned char		*color;
}						t_arena;

typedef struct			s_vis
{
	WINDOW				*code_win;
	WINDOW				*info_win;
}						t_vis;

typedef struct			s_pan_wrap
{
	t_arena				*tmp_arena;
	size_t				i;
	size_t				x;
	int					y;
	unsigned char		c;
}						t_pan_wrap;

extern t_op				g_op_tab[17];

typedef void			(*t_oper)(struct s_env *game, t_cursor *cur);

void					add_cursor(t_cursor **head, t_cursor *new);
void					add_player(t_player **head, t_player *new);
int						assign_id(t_env *game);
void					check_op(t_env *game, t_cursor *cur, t_oper *op_array);
int						decode_op(t_env *game, t_cursor *cur);
void					exe_op(t_env *game, t_cursor *cur, t_oper *op_array);
int						extract_encode_arg(t_env *game, t_cursor *cur);
void					free_cursors(t_cursor **head);
void					free_players(t_player **player);
void					free_env(t_env **arena);
int						get_op_arg(t_env *game, t_cursor *cur);
int						get_op_arg_size(int op, int arg);
t_player				*get_id(t_env *game, int id);
int						get_reg(t_env *game, int offset);
int						get_val(t_env *game, int offset, size_t size);
int						init_arena(t_env *game);
void					init_cursors(t_env *game);
int						is_valid_encode_arg(t_env *game, t_cursor *cur);
int						is_flag(t_env *game, int *i);
int						is_num(t_env *game, int i);
void					move_cursor(t_cursor *cur);
t_cursor				*new_cursor(void);
t_env					*new_env(int argc, char **argv);
t_header				*new_header(void);
t_player				*new_player(void);
void					op_add(t_env *game, t_cursor *cur);
void					op_aff(t_env *game, t_cursor *cur);
void					op_and(t_env *game, t_cursor *cur);
void					op_fork(t_env *game, t_cursor *cur);
void					op_ld(t_env *game, t_cursor *cur);
void					op_ldi(t_env *game, t_cursor *cur);
void					op_lfork(t_env *game, t_cursor *cur);
void					op_live(t_env *game, t_cursor *cur);
void					op_lld(t_env *game, t_cursor *cur);
void					op_lldi(t_env *game, t_cursor *cur);
void					op_or(t_env *game, t_cursor *cur);
void					op_st(t_env *game, t_cursor *cur);
void					op_sti(t_env *game, t_cursor *cur);
void					op_sub(t_env *game, t_cursor *cur);
void					op_xor(t_env *game, t_cursor *cur);
void					op_zjmp(t_env *game, t_cursor *cur);
int						parse_args(t_env *arena);
void					print_champions(t_env *game);
void					print_cursors(t_env *game);
void					print_arena(t_env *game);
int						read_champion(t_env *arena);
void					read_champion_code(int fd, t_player *new);
void					read_comment(int fd, t_player *new);
int						read_file(t_player *new);
void					read_magic_header(int fd, t_player *new);
void					read_null_bytes(int fd, t_player *new);
void					read_prog_name_length(int fd, t_player *new);
void					read_prog_size(int fd, t_player *new);
void					reset_op(t_cursor *cur);
void					reverse_mem(void *s, size_t n);
int						save_player(t_env *game, int rank_n, int rank_a);
int						save_champions(t_env *game, int argc, char **argv);
int						set_env(t_env *game);
void					set_op(t_env *game, t_cursor *cur);
int						set_op_arg(t_env *game, t_cursor *cur);
ssize_t					validate_registries(t_cursor *cur, t_env *game);
void					write_mem(t_env *game, int pos, int value, size_t size);
void					exec_cursors_cycle(t_env *game);
void					execute_loop(t_env *game, t_oper *op_array);
void					check_to_die(t_env *game);
void					game_loop(t_env *game);
void					print_dump(t_env *game);
void					visualizer(t_env *game);
int						print_info(t_env *game, WINDOW *win);
void					print_dump(t_env *game);
int						print_arena_ncurses(t_env *game, WINDOW *win);

#endif
