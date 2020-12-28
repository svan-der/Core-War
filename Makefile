# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lravier <lravier@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/08/02 16:55:47 by dsaripap      #+#    #+#                  #
#    Updated: 2020/09/15 12:12:23 by rheuts        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME_ASSEMBLER = asm
NAME_COREWAR = corewar
LIBFT = libft/libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
FLAG_NCURSES = -lncurses
ASSEMBLER_SRCDIR = asm_files
ASSEMBLER_OBJDIR = .obj-assembler
COREWAR_SRCDIR = corewar_files
COREWAR_OBJDIR = .obj-corewar
EXEDIR = ./

RED=\033[0;31m
GREEN=\033[0;32m
CYAN=\033[0;36m
NC=\033[0m # No Color

SRC_ASSEMBLER =	\
		asm.c \

SRC_COREWAR =	\
		corewar.c \
		cursors.c \
		free_memory.c \
		init_arena.c \
		is_flag.c \
		env.c \
		op.c \
		op_add.c \
		op_aff.c \
		op_and.c \
		op_fork.c \
		op_ld.c \
		op_ldi.c \
		op_lfork.c \
		op_live.c \
		op_lld.c \
		op_lldi.c \
		op_or.c \
		op_st.c \
		op_sti.c \
		op_sub.c \
		op_xor.c \
		op_zjmp.c \
		parse_args.c \
		printing.c \
		player.c \
		player_id.c \
		print_arena_ncurses.c \
		game_loop.c\
		check.c \
		set_op_arg.c \
		get_op_arg.c \
		exe_op.c \
		decode_op.c \
		write_mem.c \
		reverse_mem.c \
		read_champion1.c \
		read_champion2.c \
		visualizer.c

OBJ_ASSEMBLER = $(SRC_ASSEMBLER:%.c=$(ASSEMBLER_OBJDIR)/%.o)
OBJ_COREWAR = $(SRC_COREWAR:%.c=$(COREWAR_OBJDIR)/%.o)

INCL = libft/libft.a

all: $(EXEDIR)$(NAME_ASSEMBLER) $(EXEDIR)$(NAME_COREWAR)

$(LIBFT):
	@echo "${CYAN} [ * ] ${NC}Calling libft makefile"
	@$(MAKE) -C libft

$(EXEDIR)$(NAME_ASSEMBLER): $(OBJ_ASSEMBLER) $(LIBFT)
	@echo "${GREEN} [ + ] ${NC}Creating assembler object files"
	@echo "${GREEN} [ + ] ${NC}Creating assembler executable"
	@$(CC) $(FLAGS) $(OBJ_ASSEMBLER) -o $(EXEDIR)$(NAME_ASSEMBLER) $(INCL)

$(EXEDIR)$(NAME_COREWAR): $(OBJ_COREWAR) $(LIBFT)
	@echo "${GREEN} [ + ] ${NC}Creating corewar object files"
	@echo "${GREEN} [ + ] ${NC}Creating corewar executable"
	@$(CC) $(FLAGS) ${FLAG_NCURSES} $(OBJ_COREWAR) -o $(EXEDIR)$(NAME_COREWAR) $(INCL)

$(ASSEMBLER_OBJDIR)/%.o: $(ASSEMBLER_SRCDIR)/%.c $(INCL)
	@mkdir -p $(ASSEMBLER_OBJDIR)
	@$(CC) $(FLAGS) -c -o $@ $<

$(COREWAR_OBJDIR)/%.o: $(COREWAR_SRCDIR)/%.c $(INCL)
	@mkdir -p $(COREWAR_OBJDIR)
	@$(CC) $(FLAGS) -c -o $@ $<

.PHONY: clean

clean:
	@echo "${RED} [ - ] ${NC}Deleting assembler object files"
	@rm -rf $(ASSEMBLER_OBJDIR)
	@echo "${RED} [ - ] ${NC}Deleting corewar object files"
	@rm -rf $(COREWAR_OBJDIR)
	@$(MAKE) clean -C libft

fclean: clean
	@echo "${RED} [ - ] ${NC}Deleting assembler executable"
	@rm -f $(EXEDIR)$(NAME_ASSEMBLER)
	@echo "${RED} [ - ] ${NC}Deleting corewar executable"
	@rm -f $(EXEDIR)$(NAME_COREWAR)
	@echo "${RED} [ - ] ${NC}Deleting the libft.a file"
	@rm -f $(LIBFT)

re: fclean all

lldb: re
	gcc -g main.c -L. -lft

norm:
	norminette $(SRC) $(INCL) | grep -e "Error" -e "Warning" -B 1
