NAME = minishell
CC = cc #clang
CFLAGS = -Wall -Wextra -Werror -MMD -g3 -O2 -fno-builtin
SRC_PATH = src/
OBJ_PATH = obj/
SRC_NAME = main.c \
					 parsing.c \
					 signal.c \
					 utils.c \
					 ft_split.c \
					 free.c \
					 redirection.c \
					 prompt.c \
					 execution.c \
					 cd.c \
					 quotes.c
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
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
