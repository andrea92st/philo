NAME     =  philo

CC       =  cc

CFLAGS   =  -Wall -Wextra -Werror

OBJ_DIR  =  obj/

SRCS     =  src/main.c \
			src/ft_atoi.c \
			

OBJ      =  $(patsubst src/%.c, $(OBJ_DIR)%.o, $(SRCS))

MAKE_DIR =  mkdir -p

all:            $(NAME)

$(NAME):        $(OBJ)
				@$(CC) $(CFLAGS) $(OBJ) -o $@ -lreadline
				@echo "\033[1;92m======== project compiled ========\033[0m"

$(OBJ_DIR)%.o:  src/%.c
				@$(MAKE_DIR) $(dir $@)
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@rm -rf $(OBJ_DIR)
				@echo "\033[1;35m======== object files removed ========\033[0m"

fclean:         clean
				@$(RM) $(NAME)
				@echo "\033[1;36m======== executable removed  =======\033[0m"

re:             fclean all

.PHONY: clean fclean all re
