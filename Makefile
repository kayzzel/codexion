#-------------------------------- VARIABLES ----------------------------------#

NAME		=	codexion

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror
LDFLAGS		+=	-pthread
MAKEFLAGS	+=	-j $$(nproc)

DEPS		=	-MMD -MP

#-------------------------------- DIRECTORIES --------------------------------#

INCLUDE_DIR	=	includes/
UTILS_DIR	=	utils/
SRC_DIR		=	src/
OBJ_DIR		=	.build/

#-------------------------------- INCLUDES & FLAGS ---------------------------#

INCLUDES	=	-I $(INCLUDE_DIR)

#-------------------------------- SOURCE FILES -------------------------------#

MAIN_SRCS	:=	main.c

FILES		:=	parsing.c \
				utils.c \
				init_app.c \
				exit.c

SRCS		:=	$(addprefix $(SRC_DIR), $(FILES) $(MAIN_SRCS))

#-------------------------------- OBJECTS ------------------------------------#

OBJS		=	$(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))
DEPENDENCIES	=	$(OBJS:.o=.d)
BOBJS		=	$(patsubst %.c,$(OBJ_DIR)%.o,$(BONUS_SRCS))
BDEPENDENCIES	=	$(BOBJS:.o=.d)

#-------------------------------- RULES --------------------------------------#

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEPS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

compile_flags:
	@echo "-I./$(INCLUDE_DIR)" > compile_flags.txt
	@echo "$(CFLAGS)" | tr ' ' '\n' >> compile_flags.txt
	@echo "Generating compile_flags.txt done"

-include $(DEPENDENCIES)
-include $(BDEPENDENCIES)
.PHONY: all clean fclean re compile_flags
