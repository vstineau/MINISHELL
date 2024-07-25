NAME = minishell
CC = cc #clang
CFLAGS = -Wall -Wextra -Werror -MMD -g3 -O2 -fno-builtin
SRC_PATH = src/
OBJ_PATH = ../obj/
SRC_NAME = main.c \
					 parsing.c \
					 expand.c \
					 get_env.c \
					 signal.c \
					 utils.c \
					 ft_split.c \
					 free.c \
					 cmd.c \
					 tilde.c \
					 redirection.c \
					 heredoc.c \
					 heredoc_utils.c \
					 env_variables.c \
					 prompt.c \
					 cd.c \
					 quotes.c \
					 echo.c \
					 exec.c \
					 pwd.c \
					 env.c \
					 export.c \
					 unset.c \
					 exit.c \
					 exec_bonus.c \
					 apply_exec_bonus.c \
					 find_cmd.c \
					 print_export.c \
					 export_utils.c
OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -lreadline -o $(NAME) $(OBJ)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

-include $(OBJ:%.o=%.d)

all: $(NAME)

clean:
	rm -rf ../obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
