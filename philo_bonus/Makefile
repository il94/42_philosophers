#==============================================================================#
#                                   TARGETS                                    #
#==============================================================================#

NAME = philo_bonus

#==============================================================================#
#                                   COMMANDS                                   #
#==============================================================================#

CC = gcc
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -MMD
MKDIR = mkdir -p
RM = rm -f
MAKE_SILENT = make --no-print-directory
INC_LIBFT = -L libft -lft

#==============================================================================#
#                                    COLORS                                    #
#==============================================================================#

PURPLE = \033[35m
GREEN = \033[32m
YELLOW = \033[33m
END = \033[0m

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

SRC_DIR = src/
HEADER_DIR = include/
OBJ_DIR = obj/

#==============================================================================#
#                                   SOURCES                                    #
#==============================================================================#

SRC =	main.c parsing.c utils.c initialize.c run.c secure_data_access.c \
		meal_time.c meal_time_utils.c meal_monitoring.c \

#==============================================================================#
#                                   HEADERS                                    #
#==============================================================================#

HEAD_NAME = $(HEADER_DIR)/philosophers.h
INC = -I./$(HEADER_DIR)

#==============================================================================#
#                                   OBJECTS                                    #
#==============================================================================#

OBJ = $(addprefix ${OBJ_DIR}, ${SRC:.c=.o})

#==============================================================================#
#                                   MAKEFILE                                   #
#==============================================================================#

all : $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEAD_NAME) Makefile
	$(MKDIR) ${@D}
	$(CC) $(CFLAGS) $(DFLAGS) $(INC) -c $< -o $@  -lpthread

$(NAME) : $(OBJ)
	echo "$(YELLOW)Making Philosophers bonus$(END)"
	$(CC) $(CFLAGS) $(OBJ) $(INC) -o $(NAME) -g -lpthread
	echo "$(GREEN)Done$(END)"

clean :
	echo "$(PURPLE)Cleaning Philosophers's bonus objects...$(END)"
	$(RM)r $(OBJ_DIR)
	echo "$(GREEN)Done$(END)"

fclean : clean
	echo "$(PURPLE)Cleaning Philosophers bonus...$(END)"
	$(RM) $(NAME)
	echo "$(GREEN)Done$(END)"

re : fclean
	$(MAKE_SILENT) all

.PHONY : all clean fclean re
.SILENT :