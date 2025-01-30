NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude -g3 -Iincludes
OBJ_DIR = obj
SRC_DIR = src
SRC =	main.c \
		free.c \
		parser.c \
		utils.c \
		execution.c
		
		
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

all : $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME) : $(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) libft/libft.a -o $(NAME)

clean :
	rm -f -r $(OBJ_DIR)
	$(MAKE) clean -C libft/

fclean : clean
	$(MAKE) fclean -C libft/
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
