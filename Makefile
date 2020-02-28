# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/16 19:30:49 by jtaylor           #+#    #+#              #
#    Updated: 2020/02/27 23:08:46 by jtaylor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Wextra -Werror

OPT_FLAGS = -O3

PROFILE_FLAG = -pg
DEBUG_FLAG = -g3

FSANITIZE = -fsanitize=address -fsanitize=undefined

INCLUDES = -I ./libft/includes
INCLUDES += -I ./includes
INCLUDES += -I ./inc

SRC_FILE =		main.c \
				data_structs/general_tree.c \
				data_structs/general_tree_extension.c \
				data_structs/add_parent_nodes_to_tree.c \
				data_structs/queue.c \
				parse/rooms_linked_list.c \
				parse/parsing_main.c \
				parse/parse_comment_lines.c \
				parse/parse_links.c \
				parse/link.c \
				parse/print_input.c \
				errors/default_error_exit.c \
				errors/parsin_errors2.c \
				errors/parsing_erorrs.c \
				debug/print_queue.c \
				debug/print_tree_contents.c \
				debug/print_path_list_values.c \
				debug/t.c \
				debug/print_all_paths.c\
				cleanup/free_lemin_struct.c \
				cleanup/free_queue.c \
				cleanup/free_path_struct.c \
				cleanup/free_lemin_tree.c \
				cleanup/free_all_paths_struct.c \
				alg/alg_main.c \
				alg/alg_populate_edge_cases.c\
				alg/alg_misc_functions.c \
				alg/alg_get_path.c \
				alg/alg_populate_path.c \
				alg/update_residual_path.c \
				alg/print_ants_moved.c \
				alg/path_list_split_on_shared_nodes.c \
				alg/split_path_helper_func.c \
				alg/path_struct_to_list.c \
				alg/ants_per_path.c

SRC = $(addprefix ./src/, $(SRC_FILE))

.PHONY = all clean fclean re

all : $(NAME)

$(NAME) :
	@make -C ./libft
	@echo "\tBuilding $(NAME) executable\n"
	gcc $(FLAGS) $(OPT_FLAGS) $(INCLUDES) $(SRC) ./libft/libft.a ./libft/ft_printf/libftprintf.a -o $(NAME)

prof :
	@echo "\tBuilding $(NAME) prof executable\n"
	gcc $(FLAGS) $(PROFILE_FLAG) $(INCLUDES) $(SRC) ./libft/libft.a ./libft/ft_printf/libftprintf.a -o $(NAME)

debug :
	@make debug -C ./libft
	@echo "\tBuilding $(NAME) debug executable\n"
	gcc $(FLAGS) $(DEBUG_FLAG) $(INCLUDES) $(SRC) ./libft/libft.a ./libft/ft_printf/libftprintf.a -o $(NAME)

fsan :
	@make fsan -C ./libft
	@echo "\tBuilding $(NAME) executable\n"
	gcc $(DEBUG_FLAG) $(FSANITIZE) $(SRC) $(INCLUDES) ./libft/libft.a ./libft/ft_printf/libftprintf.a -o $(NAME)


clean :
	@make -C libft clean

fclean : clean
	@echo "\tRemoving $(NAME) Executable\n"
	@rm -rf $(NAME)
	@rm -rf $(NAME).dSYM
	@make -C libft fclean

re : fclean all

r :
	rm $(NAME);
	make all
