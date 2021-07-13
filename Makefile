# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbahaddi <sbahaddi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 12:28:35 by lsaidi            #+#    #+#              #
#    Updated: 2019/11/17 21:10:42 by sbahaddi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM=asm
VM=corewar

CFLAGS= -Werror -Wextra -Wall

SRC_ASM = asmb/src/main.c\
         asmb/src/befor_print_err.c\
		 asmb/src/big_endy.c\
		 asmb/src/errors.c\
		 asmb/src/errors2.c\
		 asmb/src/free.c\
		 asmb/src/get_inst.c\
		 asmb/src/get_inst_tools.c\
		 asmb/src/gnl.c\
		 asmb/src/pars_file.c\
		 asmb/src/pars_inst.c\
		 asmb/src/pars_inst2.c\
		 asmb/src/pars_name_com.c\
		 asmb/src/pars_tools.c\
		 asmb/src/print_inst.c\
		 asmb/src/print_tools.c\
		 asmb/src/set_file_name.c

SRC_VM = vm/src/degub.c \
	vm/src/ft_init.c\
	vm/src/ft_reading.c\
	vm/src/ft_vsleak.c\
	vm/src/main.c\
	vm/src/ft_player.c\
	vm/src/ft_manual.c \
	vm/src/ft_sort.c \
	vm/src/ft_read_palyer.c\
	vm/src/ft_manage_war.c \
	vm/src/ft_operation_sec1.c \
	vm/src/ft_operation_sec2.c\
	vm/src/ft_operation_sec3.c\
	vm/src/ft_operation_sec4.c\
	vm/src/ft_operation_tools.c\
	vm/src/visu_tools.c\
	vm/src/visu_init.c\
	vm/src/ft_visu_helper.c\
	vm/src/ft_start_war.c\
	vm/src/ft_kill_proc.c\
	vm/src/ft_ld.c\
	vm/src/ft_st.c\
	vm/src/ft_get_value.c\
	vm/src/ft_prepare_to_war.c\
	vm/src/ft_controle_visu.c 

HEAD_ASM = asmb/includes

HEAD_VM = vm/includes

LIB_ASM=asmb/libft/libft.a
LIB_VM=vm/libft/libft.a

_END= \x1b[0m
_RED= \x1b[31m
_GREEN= \x1b[32m

OBJ_SRC_ASM= $(SRC_ASM:.c=.o)
OBJ_SRC_VM= $(SRC_VM:.c=.o)

all : $(ASM) $(VM)

$(ASM): $(OBJ_SRC_ASM)
	@cat asm.sh
	@echo "\n$(_RED)bilding asm....$(_END)"
	@sleep 0.2
	@make -C asmb/libft
	@gcc -I$(HEAD_ASM) $(LIB_ASM) $(OBJ_SRC_ASM) $(CFLAGS) -o $(ASM)
	@echo "     make $(_GREEN)[done].$(_END)"
	
$(VM): $(OBJ_SRC_VM)
	@cat cor.sh
	@echo "\n$(_RED)bilding vm....$(_END)"
	@sleep 0.2
	@make -C vm/libft
	@gcc -I$(HEAD_VM) $(LIB_VM) $(OBJ_SRC_VM) $(CFLAGS) -o $(VM) -lncurses
	@echo "     make $(_GREEN)[done].$(_END)"

$(OBJ_SRC_ASM): %.o : %.c
	@gcc -o $@ -c $< $(CFLAGS) -I $(HEAD_ASM)
$(OBJ_SRC_VM): %.o : %.c
	@gcc -o $@ -c $< $(CFLAGS) -I $(HEAD_VM)

clean :
	@echo "$(_RED)clean src$(_END)"
	@/bin/rm -rf $(OBJ_SRC_ASM) $(OBJ_SRC_VM)
	@sleep 0.2
	@echo "$(_RED)clean libft$(_END)"
	@make -C asmb/libft clean
	@make -C vm/libft clean
	@sleep 1
	@echo "    make clean $(_GREEN)[done].$(_END)"

fclean : clean
	@echo "$(_RED)fclean $(ASM) $(VM) $(_END)"
	@/bin/rm -rf $(ASM) $(VM)
	@sleep 0.2
	@echo "$(_RED)fclean libft$(_END)"
	@make -C asmb/libft fclean
	@make -C vm/libft fclean
	@echo "    make fclean $(_GREEN)[done].$(_END)"

re : fclean all