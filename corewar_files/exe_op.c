/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_op.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rheuts <rheuts@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 15:55:26 by rheuts        #+#    #+#                 */
/*   Updated: 2020/09/14 19:40:32 by rheuts        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** void	set_op(t_env *game, t_cursor *cur)
**
**  Set the operation id based on the cursor position in the arena. If the
**  operation code is invalid set the op to 0 to move 1 byte in the check_op.
*/

void	set_op(t_env *game, t_cursor *cur)
{
	if (game->arena->code[cur->pos] >= 1 &&
	game->arena->code[cur->pos] <= REG_NUMBER)
	{
		cur->op.id = game->arena->code[cur->pos];
		cur->wait_cycles = g_op_tab[cur->op.id].n_cycle;
	}
	else
		cur->op.id = 0;
}

/*
** void	exe_op(t_env *game, t_cursor *cur, t_oper *op_array)
**
**  Execute the operation after validating. Will be a function pointer array.
*/

void	exe_op(t_env *game, t_cursor *cur, t_oper *op_array)
{
	op_array[cur->op.id](game, cur);
	if ((cur->op.id != OP_ZJMP) || (cur->op.id == OP_ZJMP && \
	cur->carry == FALSE))
		move_cursor(cur);
}

/*
** void	move_cursor(t_cursor *cur)
**
**  Move the cursor position based on whether or not an encoding byte is
**  present, the number of arguments and the size of arguments.
*/

void	move_cursor(t_cursor *cur)
{
	int	offset;
	int	i;

	offset = 1;
	i = 0;
	if (cur->op.id == 0)
	{
		cur->pos = (cur->pos + offset) % MEM_SIZE;
		return ;
	}
	if (g_op_tab[cur->op.id].encode == TRUE)
		offset += 1;
	while (i < g_op_tab[cur->op.id].n_arg)
	{
		if (cur->op.t_arg[i] > 0)
			offset += get_op_arg_size(cur->op.id, cur->op.t_arg[i]);
		i++;
	}
	cur->pos = (cur->pos + offset) % MEM_SIZE;
}

void	reset_op(t_cursor *cur)
{
	cur->op.id = 0;
	cur->op.t_arg[0] = 0;
	cur->op.t_arg[1] = 0;
	cur->op.t_arg[2] = 0;
	cur->arg[0] = 0;
	cur->arg[1] = 0;
	cur->arg[2] = 0;
	cur->wait_cycles = 0;
}

/*
** void	check_op(t_env *game, t_cursor *cur, t_oper *op_array)
**
**  Check if the operation id is valid, the argument types are valid and
**  the argument values are valid. If all is valid, execute the operation,
**  else move the cursor position.
*/

void	check_op(t_env *game, t_cursor *cur, t_oper *op_array)
{
	if (cur->op.id == FALSE)
		move_cursor(cur);
	else if (set_op_arg(game, cur) == FALSE)
		move_cursor(cur);
	else if (get_op_arg(game, cur) == FALSE)
		move_cursor(cur);
	else
		exe_op(game, cur, op_array);
	reset_op(cur);
}
