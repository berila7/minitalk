SERVER_NAME		=	server
CLIENT_NAME		=	client
SERVER_BONUS	=	server_bonus
CLIENT_BONUS	=	client_bonus

CC				=	cc
LIBFT_DIR		=	libft
FLAGS			=	-Wall -Wextra -Werror
LIBFT			=	$(LIBFT_DIR)/libft.a

SRCS			=	mandatory/client.c \
					mandatory/server.c \

BONUS_SRCS		=	bonus/client_bonus.c \
					bonus/server_bonus.c \

OBJS			=	$(SRCS:.c=.o)
BONUS_OBJS		=	$(BONUS_SRCS:.c=.o)

all: $(LIBFT) $(SERVER_NAME) $(CLIENT_NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(SERVER_NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(SERVER_NAME)

$(CLIENT_NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(CLIENT_NAME)

bonus: $(LIBFT) $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): $(BONUS_OBJS)
	$(CC) $(FLAGS) $(BONUS_OBJS) $(LIBFT) -o $(SERVER_BONUS)

$(CLIENT_BONUS): $(BONUS_OBJS)
	$(CC) $(FLAGS) $(BONUS_OBJS) $(LIBFT) -o $(CLIENT_BONUS)

mandatory/%.o: mandatory/%.c $(LIBFT) includes/minitalk.h
	$(CC) $(FLAGS) -c $< -o $@

bonus/%.o: bonus/%.c $(LIBFT) includes/minitalk_bonus.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(CLIENT_NAME) $(SERVER_NAME)
	rm -f $(CLIENT_BONUS) $(SERVER_BONUS)

re: fclean all

.PHONY: all clean fclean re