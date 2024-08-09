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
					 utils2.c \
					 utils3.c \
					 utils4.c \
					 utils5.c \
					 utils6.c \
					 utils7.c \
					 utils8.c \
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

.DEFAULT_GOAL := all

display_ascii_art :
	@echo " \0033[103m                                                                                   \0033[00m"
	@echo " \033[103m \033[30m                                            ██████████                            \033[00m"
	@echo " \033[103m \033[30m                                          ██░░░░░░░░░░██                          \033[00m"
	@echo " \033[103m \033[30m                                        ██░░░░░░░░░░░░░░██                        \033[00m"
	@echo " \033[103m \033[30m                                        ██░░░░░░░░████░░██████████                \033[00m"
	@echo " \033[103m \033[30m                            ██          ██░░░░░░░░████░░██▒▒▒▒▒▒██                \033[00m"
	@echo " \033[103m \033[30m                          ██░░██        ██░░░░░░░░░░░░░░██▒▒▒▒▒▒██                \033[00m"
	@echo " \033[103m \033[30m                          ██░░░░██      ██░░░░░░░░░░░░░░██████████                \033[00m"
	@echo " \033[103m \033[30m                        ██░░░░░░░░██      ██░░░░░░░░░░░░██                        \033[00m"
	@echo " \033[103m \033[30m                        ██░░░░░░░░████████████░░░░░░░░██                          \033[00m"
	@echo " \033[103m \033[30m                        ██░░░░░░░░██░░░░░░░░░░░░░░░░░░░░██                        \033[00m"
	@echo " \033[103m \033[30m                        ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██                      \033[00m"
	@echo " \033[103m \033[30m                        ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██                      \033[00m"
	@echo " \033[103m \033[30m                        ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██                      \033[00m"
	@echo " \033[103m \033[30m                        ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██                      \033[00m"
	@echo " \033[103m \033[30m                        ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██                      \033[00m"
	@echo " \033[103m \033[30m                        ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██                        \033[00m"
	@echo " \033[103m \033[30m                          ██░░░░░░░░░░░░░░░░░░░░░░░░░░██                          \033[00m"
	@echo " \033[103m \033[30m                            ██████░░░░░░░░░░░░░░░░████                            \033[00m"
	@echo " \033[103m \033[30m                                  ████████████████                                \033[00m"
	@echo " \0033[103m                                                                                   \0033[00m"
	@echo ""
	@echo " \0033[40m                                                                                   \0033[00m"
	@echo "\0033[37m \0033[40m              ███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██        \0033[00m"
	@echo "\0033[37m \0033[40m              ████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██        \0033[00m"
	@echo "\0033[37m \0033[40m              ██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██        \0033[00m"
	@echo "\0033[37m \0033[40m              ██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██        \0033[00m"
	@echo "\0033[37m \0033[40m              ██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████   \0033[00m"
	@echo " \0033[40m                                                                                   \0033[00m"

$(NAME): $(OBJ)
	$(eval DO_ART := 1)
	@$(CC) $(CFLAGS) -lreadline -o $(NAME) $(OBJ)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $<

-include $(OBJ:%.o=%.d)

all:  $(NAME)
	@if [ ! -z $(DO_ART) ]; then \
		$(MAKE) -s display_ascii_art;\
	fi

clean:
	rm -rf ../obj

fclean: clean
	rm -rf $(NAME)

re:
	@$(MAKE) -s fclean all

.PHONY: all clean fclean re display_ascii_art
