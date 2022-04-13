###_*_*_*_*_*_*_*_*_*_*_*_*_Makefile_ft_printf_*_*_*_*_*_*_*_*_*_*_*_*_###
## Pour compiler les bonus, si il y a en a, décommenter les lignes		##
## B_SRCS_FILES, B_SRCS_DIR, B_SRCS et dans les instructions de la ligne##
## OBJS_FILES, décommenter $(B_SRCS_FILES:.c=.o)						##

###---------------------------# VARIABLES ##---------------------------###
NAME = pipex

SRCS_FILES 		=	pipex.c \
					pipex_mem.c \

#B_SRCS_FILES	= 	 \

## Nommer les fichiers objets
OBJS_FILES 	= $(SRCS_FILES:.c=.o) #$(B_SRCS_FILES:.c=.o)

## Repertoires ##
SRCS_DIR 	= srcs/
#B_SRCS_DIR	= bonus_srcs/
OBJS_DIR	= objs/
INCLUDE_DIR = include/
LIBFT_DIR 	= 42Qc_libft/

SRCS 		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
#B_SRCS 		= $(addprefix $(B_SRCS_DIR), $(B_SRCS_FILES))
OBJS 		= $(addprefix $(OBJS_DIR), $(OBJS_FILES))
VPATH 		= $(SRCS_DIR) $(B_SRCS_DIR)

## Compilations et archivage
CC 			= gcc
CFLAGS 		= -Wall -Werror -Wextra -g
AR 			= ar -cr

## Autres Fonctions
RM 			= rm -rf
NORMINETTE 	= norminette
LIBFT		= $(MAKE) --silent -C $(LIBFT_DIR)

## Colors code
END			= \033[0m
BOLD		= \033[1m
ITALIC		= \033[3m
URL			= \033[4m
BLINK		= \033[5m
BLINK2		= \033[6m
SELECTED	= \033[7m

BLACK		= \033[30m
RED			= \033[31m
GREEN		= \033[32m
YELLOW		= \033[33m
BLUE		= \033[34m
VIOLET		= \033[35m
BEIGE		= \033[36m
WHITE		= \033[37m

###----------------------------## REGLES ##----------------------------###
all: obj $(NAME)

$(OBJS_DIR)%.o:%.c
	@${CC} ${CFLAGS} -I${LIBFT_DIR} -I${INCLUDE_DIR} -I. -o $@ -c $<

$(NAME): $(OBJS)
	@${LIBFT}
	@${CC} ${OBJS} -L${LIBFT_DIR} -lft -o ${NAME} -lm
	@echo "\n${BLUE}${BOLD}An executable '${BLINK2} pipex ${END}${BLUE}${BOLD}' have been created successfully!${END}"
	@sleep 1

#bonus: $(NAME) $(BONUS_OBJS)
#	@${ARCHIVE} ${NAME} ${BONUS_OBJS}
#	@echo "${BONUS_OBJS} ${GREEN} ${BOLD}\n\nObjects files And bonus objects files are added to the archive libftprintf.a correctly\n${END}"

obj:
	@mkdir -p ${OBJS_DIR}

test: norm all
	@echo "\n${GEIGE}${BOLD}Also the norminette have been checked on the push_swap sources and headers files.${END}\nIf you need to continue with valgrind to look for some leaks retry with ${VIOLET}make leaks${END}"
	sleep 8

leaks: re
	valgrind --leaks-check=full --show-leak-kinds=all -s ./test

norm: fclean
	@$(NORMINETTE) ${SRCS_DIR} ${INCLUDE_DIR}

clean:
	@${RM} ${OBJS}
	@echo "\n${BOLD}${GREEN}The pipex objects files have been ${RED}deleted ${END}${BOLD}${GREEN}correctly.${END}"
	@sleep 0.5

fclean:	clean
	@${RM} ${NAME} ${NAME}.dSYM ${OBJS_DIR}
	@$(LIBFT) fclean
	@echo "\n${BOLD}${GREEN}The executable file ' ${BLUE}pipex${GREEN} ' have been ${RED}deleted ${END}${BOLD}${GREEN}too.${END}"
	@sleep 0.5
re:	fclean all

phony: all obj test norm leaks clean fclean re bonus
