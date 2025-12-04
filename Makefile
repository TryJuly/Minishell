#################################################################################################################
#                                           VARIABLES SET                                                       #
#################################################################################################################
NAME = minishell

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

SRCS = main.c init_struct.c ft_clean.c parsing_v1.c

SRCS_BONUS =

INCLUDES = header.h

LIBFT = ./libft/
LIBFT_A= ./libft.a

OBJS = ${addprefix ${OBJ_DIR}/,${SRCS:.c=.o}}
OBJ_DIR = objets/
#################################################################################################################
#                                           RULES COMPILATION                                                   #
#################################################################################################################
all: ${LIBFT_A} ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} ${LIBFT_A} ${EXTRA} -I ${INCLUDES} -o ${NAME} ${LDFLAGS}

${OBJ_DIR}/%.o: %.c ${INCLUDES}
	@mkdir -p ${OBJ_DIR}
	${CC} ${FLAGS} -c $< -o $@

${LIBFT_A}:
	@make -C ${LIBFT}
	@cd ${LIBFT} && cp ${LIBFT_A} ..

#################################################################################################################
#                                           RULES CLEAN                                                         #
#################################################################################################################
clean:
	rm -rf ${OBJ_DIR}/ ${OBJS} ${OBJ_DIR_BONUS}/ ${OBJS_BONUS}

clean_lib:
	@make clean -C ${LIBFT}

fclean: clean
	rm -rf ${NAME} ${BONUS_NAME} ${LIBFT_A}

fclean_lib: clean_lib
	@make fclean -C ${LIBFT}
	@rm -rf ${LIBFT_A}

re: fclean fclean_lib all
#################################################################################################################
#                                           NO RELINK                                                           #
#################################################################################################################

.PHONY: all clean fclean re clean_lib fclean_lib bonus

#################################################################################################################
#                                           BONUS	                                                            #
#################################################################################################################
BONUS_NAME =

OBJS_BONUS = ${addprefix ${OBJ_DIR_BONUS}/,${SRCS_BONUS:.c=.o}}
OBJ_DIR_BONUS = objets_bonus

${OBJ_DIR_BONUS}/%.o: %.c ${INCLUDES}
	@mkdir -p ${OBJ_DIR_BONUS}
	${CC} ${FLAGS} -c $< -o $@

${BONUS_NAME}: ${OBJS_BONUS}
	${CC} ${FLAGS} ${OBJS_BONUS} ${LIB} ${EXTRA} -I ${INCLUDES} -o ${BONUS_NAME}

bonus: ${MINILIBX_A} ${LIBFT_A} ${BONUS_NAME}